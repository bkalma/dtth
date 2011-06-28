<?php

function dtth_signin_button($service, $param = FALSE) {
  drupal_add_js( drupal_get_path('module', 'dtth') .'/js/login.js');
  if ($param) {
    $query['param'] = $param;
    $url = url('signin/'.$service.'/'.$param, array('query' => $query, 'absolute' => TRUE));
  } else {                                                
    $url = url('signin/'.$service, array('absolute' => TRUE));
  }        
  switch ($service) {
    case 'twitter':
      return '<a title="twitter" href="#" id="login_tw" onclick="window.open(\''.$url.'\',\''.$service.'\', \'menubar=no,width=620,height=440,toolbar=no,scrollbars=true\'); return false;">'.$service.'</a>';
    break;
    case 'facebook':   
      $attr = array('perms' => 'email');   
      switch ($param) {
        case 'dtth_signin_form':
          $attr['onlogin'] = 'dtth_facebook_signin_onlogin_ready();';
        break;
        case 'dtth_upload2_form':
          $attr['onlogin'] = 'dtth_facebook_upload2_onlogin_ready();';
        break;         
        default:
          $attr['onlogin'] = 'dtth_facebook_onlogin2_ready();';
        break;
      }
      //return '<a title="facebook" href="#" id="login_fb" onclick="window.open(\''.$url.'\',\''.$service.'\', \'menubar=no,width=620,height=440,toolbar=no,scrollbars=true\'); return false;">'.$service.'</a>';            
      $facebook_link = fbconnect_render_button($attr);
      return $facebook_link;
    break;
  }  
  //return l(t('twitter'), 'twitter/redirect', array('attributes' => array('id' => 'login_tw'), 'html' => TRUE));
}


function dtth_signin_page() {
  global $user;
    
  $form_id = 'dtth_signin_form';  
  $form_state = array(
    'title' => t('Upload Dog Tilting'),
    'ajax' => TRUE,    
  );
  $content = ctools_modal_form_wrapper($form_id, $form_state);
  if (empty($content) || (bool) $user->uid) {           
    $content = array();                   
    $content[] = ctools_modal_command_loading(); 
    $content[] = ctools_ajax_command_eval('$(\'#dtth-caption-form a.post_btn\').toggle();');
    $content[] = ctools_ajax_command_eval('$(\'#dtth-caption-form input.post_btn\').toggle();');
    $content[] = ctools_ajax_command_eval('$(\'#dtth-caption-form input.post_btn\').click();');
    $content[] = ctools_modal_command_dismiss();    
  }
  ctools_ajax_render($content);
}

function dtth_signin_form(&$form_state) {
   // since when user changed session will be destroyed, then we need to restore form state storage from cache 
  if ($_POST['op'] == t('Login')) {
    $form_build_id = $_POST['form_build_id'];    
    if ($cached = cache_get('storage_' . $form_build_id, 'cache_form')) {      
      $form_state['storage'] = $cached->data;
    } 
  } 
  
  // $form['#post'] is needed because http://drupal.org/node/678158#comment-2584406  
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['#post'] = array();
    
  drupal_add_js( drupal_get_path('module', 'dtth') .'/js/login_modal.js');
           
  /*$attr = array(
    'perms' => 'email',
    'onlogin' => 'dtth_facebook_signin_onlogin_ready();',
  );*/      
  
  $form_state['title'] = t('Please log in with Facebook or Twitter');
  
  $facebook_link = dtth_signin_button('facebook', 'dtth_signin_form');    
  $twitter_link = dtth_signin_button('twitter','dtth_signin_form');
  $form['signin_info'] = array(
        '#type' => 'markup',
        '#value' => t('Please login first to continue'),
  );      
  $form['signin'] = array(
    '#type' => 'markup',
    '#value' => '<div id="user_login" class="png_bg">		     		    
    '.$facebook_link.'		    
    '.$twitter_link.'</div>'
  ); 
  
  $form['login'] = array(
    '#type' => 'markup',
    '#value' => t('Please login first to continue'),
  );
  
  $form['signin_service'] = array(
    '#type' => 'hidden',
    '#default_value' => 'twitter',
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Login'),
  );    
  
  $form['#theme'] = 'dtth_signin_form';
  
  return $form;        
}

function theme_dtth_signin_form($form) {
  if ($form['#parameters'][1]['storage']['step']) {
    $step = $form['#parameters'][1]['storage']['step'];
  } else {
    $step = 'login';        
  }
  $output = '';
  switch ($step) {
    case 'login':            
      $output = '<div id="upload_container" class="'.$step.'">
      '.drupal_render($form['signin_info']).'
      '.drupal_render($form['signin']).'
      </div>';
    break;
  }
  
  $output .= '<div style="display: none">'.drupal_render($form).'</div>';  
  return $output;
}  

function dtth_signin_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  if ($values['op'] == t('Login')) {
    if ($values['signin_service'] == 'facebook') {
      $connect = dtth_signin_fbconnect();
      if ($connect) {
        $form_state['rebuild'] = FALSE;
        $form_state['executed'] = TRUE;
      } else {
        $form_state['rebuild'] = TRUE;      
      }
    } else if ($values['signin_service'] == 'twitter') {
      $form_state['rebuild'] = FALSE;
      $form_state['executed'] = TRUE;
    }        
  }          
}

function dtth_signin_fbconnect() {
  $fbuid = fbconnect_get_fbuid();
  if (user_is_anonymous()) {
    if ($fbuid) {
      $uid = _is_fbconnect_user($fbuid);
      if ($uid) {
        $form_state['values']['uid']   = $uid;
        $form_state['values']['fbuid'] = $fbuid;
                
        $account = user_load($uid);        
      } else {
        $data  = fbconnect_get_user_info('name, email');
      
        $newname = $conf['fast_reg_autoname']? _fbconnect_get_username($data['name']) : $data['name'];
        $form_state['values']['name']       = $newname;
        $form_state['values']['mail']       = $data['email'];
        $form_state['values']['pass']       = user_password();
        $form_state['values']['status']     = 1;
        $form_state['values']['fb_visible'] = 1;
        $form_state['values']['fb_avatar']  = 1;
        
        drupal_validate_form('user_register', $form, $form_state);      
        $account = user_save(NULL, $form_state['values']);
        fbconnect_register($account->uid, $fbuid);        
        $data['fb_avatar']  = 1;
        $data['fb_visible'] = 1;
        user_save($account, $data);
      }
      user_external_login($account);
      module_invoke('rules', 'invoke_event', 'fbconnect_user_login', $account);
      return TRUE;
    } else {            
    }
  }
  return FALSE;
}

function dtth_signin($service) {
  $param = arg(2);
  switch ($service) {
    case 'facebook':
      return dtth_signin_facebook($param);
    break;
    case 'twitter':
      return dtth_signin_twitter($param);
    break;
  }
}

function dtth_signin_callback($service) {
  $param = arg(3);
  switch ($service) {
    case 'facebook':
      return dtth_signin_callback_facebook($param);
    break;
    case 'twitter':
      return dtth_signin_callback_twitter($param);
    break;
  }
}

function dtth_signin_callback_facebook($param = '') {
  switch ($param) {
    case 'dtth_upload2_form':
      drupal_add_js("$(document).ready(function() {
      window.opener.$('#dtth-upload2-form').append('<input type=\"hidden\" name=\"op\" value=\"Login\">');
      window.opener.$('#dtth-upload2-form').submit();                
      window.close();
      });","inline");
    break;
    case 'dtth_signin_form':
      drupal_add_js("$(document).ready(function() {
      window.opener.$('#dtth-signin-form').append('<input type=\"hidden\" name=\"op\" value=\"Login\">');
      window.opener.$('#dtth-signin-form').submit();                
      window.close();
      });","inline");
    break;
    default:
      drupal_add_js("$(document).ready(function() {  
  window.opener.location.reload(false);  
  window.close();
  });","inline");
    break;
  }                  
  return '.';  
}

function dtth_signin_facebook($param = '') {
  /*drupal_add_js("
$('a.fb_button.fb_button_medium').ready(function () {
  alert('test');
  $(this).click();
});","inline");*/
  drupal_add_js( drupal_get_path('module', 'dtth') .'/js/login.js');
  drupal_add_js("$(document).ready(function() {
  Drupal.settings.fbconnect.loginout_mode = 'auto';
  });",'inline');
  if (variable_get('fbconnect_fast_reg', 0) && variable_get('fbconnect_reg_options', 0)) {
    $attr = array('perms' => 'email');
  }                                   
  
  if ($param) {
    $_REQUEST['destination'] = 'signin/facebook/callback/' . $param;
  } else {
    $_REQUEST['destination'] = 'signin/facebook/callback';
  }
  
  $facebook_link = fbconnect_render_button($attr);
  return $facebook_link;
}                                           

function dtth_signin_twitter($param) {
  module_load_include('lib.php', 'oauth');
  module_load_include('lib.php', 'twitter');
  module_load_include('inc', 'twitter');

  $key = variable_get('twitter_consumer_key', '');
  $secret = variable_get('twitter_consumer_secret', '');
  $twitter = new TwitterOAuth($key, $secret);
  $token = $twitter->get_request_token();

  $_SESSION['twitter_oauth']['token'] = $token;  
  $query = $_GET;
  unset($query['q']);
  if ($param) {
    $_SESSION['twitter_oauth']['destination'] = url('signin/twitter/callback/'. $param, array('query' => $query, 'absolute' => TRUE));
  } else {
    $_SESSION['twitter_oauth']['destination'] = url('signin/twitter/callback', array('query' => $query, 'absolute' => TRUE));
  }  
  $_SESSION['twitter_oauth']['signin'] = TRUE;  
  drupal_goto($twitter->get_authenticate_url($token));
}

function dtth_signin_callback_twitter_submit(&$form, &$form_state) {
  global $user;

  $success = FALSE;

  $key = variable_get('twitter_consumer_key', '');
  $secret = variable_get('twitter_consumer_secret', '');
  $response = $form_state['twitter_oauth']['response'];

  $account = user_external_load($response['user_id']);  
  if (isset($account->uid)) {
    dtth_user_external_login($account, $response);
    $success = TRUE;
  }
  elseif ($uid = db_result(db_query("SELECT uid FROM {twitter_account} WHERE twitter_uid= %d", $response['user_id']))) {
    // We have an existing twitter account - set it up for login
    $account = user_load($uid);
    $edit["authname_twitter"] = $response['user_id'];
    user_save($account, $edit);
    $user = $account;
    $success = TRUE;
  }
  else {
    // No existing user account, let's see if we can register.
    if (variable_get('twitter_signin_register', 0)) {
      // Check for a nickname collision
      $account = user_load(array('name' => $response['screen_name']));
      if (!$account->uid) {
        $edit = array(
          'name' => $response['screen_name'],
          'pass' => user_password(),
          'init' => $response['screen_name'],
          'status' => 1,
          "authname_twitter" => $response['user_id'],
          'access' => time(),
        );
        $account = user_save('', $edit);
        $user = $account;
        $success = TRUE;
      }
      else {
        drupal_set_message(t('The nickname %name is already in use on this site, please register below with a new nick name, or @login to continue.', array('%name' => $response['screen_name'], '@login' => url('user/login'))), 'warning');
      }
    }
    else {
      drupal_set_message(t('Please complete the following registration form to create your new account on %site', array('%site' => variable_get('site_name', ''))));
    }
  }    
  
  if (!$success) {
    $_SESSION['twitter']['values'] = $response;
    drupal_goto('user/register');
  }
}

function dtth_twitter_signin_callback_redirect_submit(&$form, &$form_state) {
  //$form_state['redirect'] = 'signin/twitter/callback';
  /*print 'ok';
  exit();*/
}

function dtth_signin_callback_twitter($param = '') {  
  switch ($param) {
    case 'dtth_upload2_form':
      drupal_add_js("$(document).ready(function() {
      window.opener.$('#dtth-upload2-form').append('<input type=\"hidden\" name=\"op\" value=\"Login\">');
      window.opener.$('#dtth-upload2-form').submit();                
      window.close();
      });","inline");
    break;
    case 'dtth_signin_form':
      drupal_add_js("$(document).ready(function() {
      window.opener.$('#dtth-signin-form').append('<input type=\"hidden\" name=\"op\" value=\"Login\">');
      window.opener.$('#dtth-signin-form').submit();                
      window.close();
      });","inline");
    break;
    default:
      drupal_add_js("$(document).ready(function() {  
  window.opener.location.reload(false);  
  window.close();
  });","inline");
    break;
  }                  
  return '.';
}

function dtth_user_external_login($account, $edit = array()) {
  $form = drupal_get_form('user_login');

  $state['values'] = $edit;
  if (empty($state['values']['name'])) {
    $state['values']['name'] = $account->name;
  }

  // Check if user is blocked or denied by access rules.
  user_login_name_validate($form, $state, (array) $account);
  if (form_get_errors()) {
    // Invalid login.
    return FALSE;
  }

  // Valid login.
  global $user;
  $user = $account;
  user_authenticate_finalize($state['values']);
  return TRUE;
}