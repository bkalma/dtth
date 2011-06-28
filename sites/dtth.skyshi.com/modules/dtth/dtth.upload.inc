<?php

function dtth_upload2_page() {
  global $user;
  
  $js = TRUE;      
  ctools_include('node.pages', 'node', '');
  //include_once(drupal_get_path('module','node') . '/node.pages.inc');
  $GLOBALS['dtth_upload_page'] = TRUE;
  $node = new stdClass();
  $node->type = 'dog';  
  $node->uid = $user->uid;
  $node->name = $user->name;
  $node->comment = 2;  
  $title = 'hello';   
  if ($js) {
    //ctools_modal_render($title, $content);
    $form_id = 'dtth_upload2_form';
    $form_state = array(
      'title' => t('Upload Dog Tilting'),
      'ajax' => TRUE,
      'args' => array($node),
    );
                      
    $content = ctools_modal_form_wrapper($form_id, $form_state);        
    if (empty($content)) {             
      // empty $output signifies success, so we'll use it as our $commands
      // array.
      //$redirect = explode("/", $form_state['redirect']);
      //$nid = $redirect[1];
      $nid = $form_state['nid'];
      $content = array();
      $content[] = ctools_modal_command_loading();
      $content[] = ctools_ajax_command_redirect('node/'. $nid);
      //$content[] = ctools_ajax_command_redirect($form_state['redirect']);
      /*$node = node_load($nid);
      $title = $node->title;
      $output = node_view($node, FALSE, FALSE);
      $content[] = ctools_modal_command_display($title, $output);
      $content[] = ctools_ajax_command_css('#modalContent .pre_post_box_action .fb', array('position' => 'relative'));*/
      //$content[] = ctools_ajax_command_eval('$(\'#modalContent .node_'.$node->nid.' a.fb\').attr(\'title\',\'Share on Facebook or Twitter\').tooltip({api: true}).show();');
      //$content[] = ctools_ajax_command_eval('$(\'#modalContent .node_'.$node->nid.' a.fb\').attr(\'title\',\'Share on Facebook or Twitter\');');
      /*$content[] = ctools_ajax_command_append('#modalContent .pre_post_box_action .fb', '<div class="ballon" style="position: absolute; left: -80px;">
<div class="ballon_inner">Congrats! Your best friend is on the path to fame! With a little help from Facebook and Twitter fame could be even closer than you think!</div></div>');*/      
    }
    ctools_ajax_render($content);
  } else {
    
  }
}


function dtth_upload2_form(&$form_state) {
  global $user;
  
  // since when user changed, session will be destroyed, then we need to restore form state storage from cache 
  if ($_POST['op'] == t('Login')) {
    $form_build_id = $_POST['form_build_id'];
    if ($cached = cache_get('storage_' . $form_build_id, 'cache_form')) {
      $form_state['storage'] = $cached->data;
    } 
  } 
  
  if (!isset($form_state['storage']['step'])) {    
    $form_state['storage']['step'] = 'default';    
  }    
  
  // $form['#post'] is needed because http://drupal.org/node/678158#comment-2584406
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['#post'] = array();  
  
  $values = $form_state['storage']['values'];  
      
  $step = $form_state['storage']['step'];  
  switch ($step) {  
    case 'login':            
      drupal_add_js( drupal_get_path('module', 'dtth') .'/js/login.js');
      drupal_add_js( drupal_get_path('module', 'dtth') .'/js/login_modal.js');      
      /*$attr = array(
        'perms' => 'email',
        'onlogin' => 'dtth_facebook_onlogin_ready();',
      );*/      
      
      //$facebook_link = fbconnect_render_button($attr);
      $facebook_link = dtth_signin_button('facebook', 'dtth_upload2_form');    
      $twitter_link = dtth_signin_button('twitter','dtth_upload2_form');
      $form_state['title'] = t('Please log in with Facebook or Twitter');
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
    break;
    
    case 'newbreed':            
      $form_state['title'] = t('New Breed Name');
      $form['newbreed_name'] = array(
        '#type' => 'textfield',
        '#resizable' => FALSE,
        '#size' => 40,
        '#attributes' => array(          
          'placeholder' => t('Please type new breed name'),
        ),         
        '#default_value' => $values['newbreed_name'],       
      );
      /*$form['newbreed_desc'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#size' => 40,
        '#attributes' => array(          
          'placeholder' => t('Please type breed description'),
        ),        
      );*/
      $form['newbreed_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Add New Breed'),         
        '#attributes' => array('class' => 'upload_add_btn'),               
      );
      $form['newbreed_cancel'] = array(
        '#type' => 'submit',
        '#value' => t('Cancel'),                        
        '#attributes' => array('class' => 'upload_cancel_btn'),
      );
    break;
    
    case 'default':
      $form_state['title'] = t('Upload Dog Tilting');
      drupal_add_js( drupal_get_path('module', 'dtth') .'/js/upload.js');
      $tilt_list = array();
      if ($values['tilts']) {        
        foreach ($values['tilts'] as $file) {                            
          //$tilt_list[] = array(theme('imagecache', 'small', $file['filepath']), $file['filename']); 
          //$tilt_list[] = array(theme('image', $file['filepath'], NULL, NULL, array()), $file['filename']);
          $focus_rect = explode(",", $file['data']['focus_rect']);
          
          $width_ratio =  100 / 540;
          $height_ratio =  100 / 540; 
                              
          if ($focus_rect[2] == 0) {
            $rx = 0;
          } else {
            $rx = 540 / $focus_rect[2];
          }                    
          
          if ($focus_rect[3] == 0) {
            $ry = 0;
          } else {
            $ry = 540 / $focus_rect[3];
          }
          
          $width = round($rx * $file['data']['image']['width'] * $width_ratio) . 'px';
          $height = round($ry * $file['data']['image']['height'] * $height_ratio) . 'px';
          $marginleft = -1 * (round($rx * $focus_rect[0] * $width_ratio))  . 'px';
          $margintop = -1 * (round($ry * $focus_rect[1] * $height_ratio))  . 'px';
          $attributes = array('style' => 'width: '.$width.';height: '.$height.'; margin-left: '. $marginleft.'; margin-top: '. $margintop.';');
          $tilt_list[] = array('<div style="width: 100px; height: 100px; overflow: hidden;">'.theme('image', $file['filepath'], NULL, NULL, $attributes). '</div>', $file['filename']);
        }
        $form['tilt_list'] = array(
          '#type' => 'markup',
          '#value' => theme('table', NULL, $tilt_list),
        );
      }      
      $form['tilt'] = array(
        '#type' => 'file',
        '#attributes' => array(
          'placeholder' => t('Upload Your Pup Tilting')
        ),        
      );
      $form['upload'] = array(
        '#type' => 'submit',
        '#value' => t('Upload'),
        '#attributes' => array(
          'class' => 'upload_browse_a',
        ),
      );
      $form['breed'] = array(
        '#type' => 'textfield',
        '#attributes' => array(
          //'placeholder' => t('What Breed is Your Dog?'),
          'placeholder' => t('Breed'),
        ),
        '#default_value' => $values['breed'],
        '#autocomplete_path' => 'upload/breed/js',         
      );
      

      $form['name'] = array(
        '#type' => 'textfield',
        '#attributes' => array(
          'placeholder' => t('What\'s Your Dogs Name?'),
        ),
        '#default_value' => $values['name'],        
      );
      $form['caption'] = array(
        '#type' => 'textarea',
        '#resizable' => FALSE,
        '#rows' => 5,        
        '#attributes' => array(
          //'placeholder' => t('What\'s Going Through Your Dog\'s Head'),
          'placeholder' => t('Caption (Optional)'),
        ),        
        '#default_value' => $values['caption'],
      );      
      $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#attributes' => array('class' => 'upload_submit_btn'),
      );
      
      $form['addnewbreed'] = array(
        '#type' => 'submit',
        '#value' => t('Add New Breed Form'),        
      );
    break;    
    case 'upload':
      $form_state['title'] = t('Resize Photo');
      $tilt = $values['tilt'];
      
      //$path = drupal_get_path('module', 'imagefield_focus');
      //drupal_add_js( drupal_get_path('module', 'imagefield_focus') .'/imgfocus/jquery.imgfocus.min.js');
      //drupal_add_js( $path .'/imagefield_focus.js');
      //drupal_add_css(drupal_get_path('module', 'imagefield_focus') .'/imgfocus/jquery.imgfocus.css');
      //drupal_add_css($path .'/imagefield_focus.css');
      drupal_add_js(drupal_get_path('module', 'dtth') .'/Jcrop/js/jquery.Jcrop.min.js');
      drupal_add_css(drupal_get_path('module', 'dtth') .'/Jcrop/css/jquery.Jcrop.css');
      drupal_add_js( drupal_get_path('module', 'dtth') .'/js/upload_tilt.js');      
      
      $form['tilt_info'] = array(
        '#type' => 'value',
        '#value' => $tilt,
      );
      $form['tilt_focus_rect'] = array(
        '#type' => 'hidden',
        '#default_value' => '',
        '#attributes' => array(
          'class' => 'tilt_image_focus_rect',
        ),
      );
      
      $image = image_get_info($tilt['filepath']);
      
      $settings['upload_tilt_data']['width'] = $image['width'];
      $settings['upload_tilt_data']['height'] = $image['height'];
      drupal_add_js($settings, 'setting');
            
      $form['tilt_image'] = array(
        '#type' => 'markup',
        //'#value' => '<div class="tilt_focus-focus focus-box">test<img src="'. file_create_url($tilt['filepath']) .'" alt="'. $info[0] .'x'. $info[1] .'" style="display:none;" /></div>',
        '#value' => '<div class="tilt_focus"><img src="'. file_create_url($tilt['filepath']) .'" style="visibility: hidden;"/></div>',
        //'#value' => '<div class="tilt_focus">'.theme('imagecache', 'upload_jcrop', $tilt['filepath']) .'</div>',
        //'#value' => '<div class="imagefield-focus focus-box">test<img src="'. file_create_url($tilt['filepath']) .'" alt="'. $info[0] .'x'. $info[1] .'"  /></div>',
      );
      
      /*$form['tilt_file'] = array(
        '#type' => 'markup',
        '#value' => '<pre>'.print_r($form_state['values']['tilts'], TRUE). '</pre>',        
      );*/
      $form['continue'] = array(
        '#type' => 'submit',
        '#value' => t('Continue'),
        '#attributes' => array(
          'class' => 'crop_continue_btn',
        ),
      );
    break;
  }
  
  //$form['markup']['#value'] = '<pre>' . print_r($values, TRUE) . '</pre>';
  
  $form['#theme'] = 'dtth_upload2_form';
    
  return $form;
}

function dtth_upload2_form_validate($form, &$form_state) {
  if (isset($form_state['storage']['values']) && isset($form_state['values'])) { 
    $values = $form_state['values'] + $form_state['storage']['values'];
    $op = $values['op'];            
    switch ($op) {
      case t('Submit'):
        if (empty($values['name'])) {
          form_set_error('name', t('Please define Dog\'s name'));
        }
        if (empty($values['breed'])) {
          form_set_error('breed', t('Please define Dog\'s Breed'));
        } else {
          $tid = db_result(db_query("SELECT tid FROM {term_data} WHERE name='%s' AND vid=%d", $values['breed'], VOCABULARY_BREED));
          if (!$tid) {
            form_set_error('breed', t('Dog\'s Breed is not exist, please add new breed if you want to add new breed'));
          }
        }
        /*if (empty($values['tilts'])) {
          form_set_error('tilt', t('Please define Dog\'s Tilt'));
        }*/
      break;
      case t('Upload'):
        /*if (empty($values['tilt'])) {
          form_set_error('tilt', t('Please define Dog\'s Tilt'));
        } */        
      break;
    }  
  }
}  

function dtth_upload2_form_submit($form, &$form_state) {
  global $user;
  
  $values = $form_state['values'];  
  $step = $form_state['storage']['step'];
  $op = $values['op'];
  
  if (!isset($form_state['storage']['values'])) {
    $form_state['storage']['values'] = array();    
  }                     
    
  switch ($op) {
    case t('Cancel'):
      $form_state['rebuild'] = TRUE;
      $form_state['storage']['step'] = 'default';
    break;     
    case t('Add New Breed Form'):                  
      //$form_state['values']['newbreed_name'] = $values['breed'];
      $form_state['storage']['values'] = $form_state['values']  + $form_state['storage']['values'];      
      $form_state['rebuild'] = TRUE;
      $form_state['storage']['step'] = 'newbreed';                     
    break;
    case t('Add New Breed'):
      $newbreed = trim($values['newbreed_name']);
      // check term is exist or not
      $term = db_fetch_object(db_query("SELECT * FROM {term_data} WHERE vid=%d AND name='%s'", VOCABULARY_BREED, $newbreed));
      if (!$term) {
        $newbreed = array(
          'name' => $newbreed,          
          'vid' => VOCABULARY_BREED,
        );
        taxonomy_save_term($newbreed);
        $newbreed = db_fetch_object(db_query("SELECT * FROM {term_data} WHERE vid=%d AND name='%s'", VOCABULARY_BREED, $newbreed['name']));
        //db_query("UPDATE {term_data} SET status=0 WHERE tid=%d", $newbreed->tid);
        db_query("UPDATE {term_data} SET status=1 WHERE tid=%d", $newbreed->tid);
      }                        
      $form_state['values']['breed'] = $values['newbreed_name'];      
      $form_state['storage']['values'] = $form_state['values']  + $form_state['storage']['values'];      
      $form_state['rebuild'] = TRUE;
      $form_state['storage']['step'] = 'default';                     
    break;         
    case t('Login'):      
      $form_state['storage']['values'] = $form_state['values']  + $form_state['storage']['values'];
      
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
            
      if ((bool) $user->uid) {
        //$form_state['rebuild'] = TRUE;
        //$form_state['storage']['step'] = 'default';
        
        // end process
        $form_state['rebuild'] = FALSE;
        $form_state['executed'] = TRUE;        
      } else {
        $form_state['rebuild'] = TRUE;
        $form_state['storage']['step'] = 'login';        
      }
    break;
    case t('Upload'):
      $limits = _upload_file_limits($user);
      $validators = array(
        'file_validate_extensions' => array($limits['extensions']), 
        'file_validate_image_resolution' => array($limits['resolution']), 
        'file_validate_size' => array($limits['file_size'], $limits['user_size']),
      );
      
      $path = file_directory_path() . '/upload';
      dtth_upload_check_directory($path, FILE_CREATE_DIRECTORY);
      $path = file_directory_path() . '/upload/u'.$user->uid;
      dtth_upload_check_directory($path, FILE_CREATE_DIRECTORY);
      $path = file_directory_path() . '/upload/u'.$user->uid.'/tilt';
      dtth_upload_check_directory($path, FILE_CREATE_DIRECTORY);
            
      if ($file = file_save_upload('tilt', $validators, $path)) {        
        $file->description = $file->filename;        
        $file->new = TRUE;
        $form_state['values']['tilts'] = $form_state['storage']['values']['tilts'];         
        $form_state['values']['tilts'][$file->fid] = (array) $file;
        $form_state['values']['tilt'] = (array) $file;
      } else {
        /*foreach ($form_state['storage']['values']['tilts'] as $fid => $file) {        
          $form_state['values']['tilt'] = (array) $file;
        } */              
      }      
      
      $image = image_get_info($file->filepath);              
      if ($image['width'] < 540 || $image['height'] < 540 ) {
        form_set_error('tilt', t('Please upload photo with minimum size 540x540'));
        return;
      }
                            
      //print_r($form_state['values']);
      //print_r($form_state['storage']['values']);
      //exit();
      $form_state['rebuild'] = TRUE;
      $form_state['storage']['step'] = 'upload';
      $form_state['storage']['values'] = $form_state['values'] + $form_state['storage']['values'];  
    break;
    case t('Continue'):
      $file = $values['tilt_info'];
      $focus_rect = $values['tilt_focus_rect'];
      $form_state['values']['tilts'] = $form_state['storage']['values']['tilts'];
      $form_state['values']['tilts'][$file['fid']]['data']['focus_rect'] = $focus_rect;
      $form_state['values']['tilts'][$file['fid']]['data']['crop_rect'] = '';
      $form_state['values']['tilts'][$file['fid']]['data']['image'] = image_get_info($file['filepath']);
      $form_state['rebuild'] = TRUE;
      $form_state['storage']['step'] = 'default';      
      $form_state['storage']['values'] = $form_state['values']  + $form_state['storage']['values'];
      
      // override form_state to End
      //$form_state['rebuild'] = FALSE;
      //$form_state['executed'] = TRUE;  
    break;
    case t('Submit'):  
      if ($file = file_save_upload('tilt', $validators, file_directory_path())) {        
        $file->description = $file->filename;        
        $file->new = TRUE;
        $form_state['values']['tilts'] = $form_state['storage']['values']['tilts'];         
        $form_state['values']['tilts'][$file->fid] = (array) $file;
        $form_state['values']['tilt'] = (array) $file;
      }
      
      $form_state['storage']['values'] = $form_state['values']  + $form_state['storage']['values'];
      
      if (!(bool) $user->uid) {               
        $form_state['rebuild'] = TRUE;
        $form_state['storage']['step'] = 'login';
      } else {
        $form_state['rebuild'] = FALSE;
        $form_state['executed'] = TRUE;
      }              
      
      // override form_state to 'Upload'
      //$form_state['rebuild'] = TRUE;
      //$form_state['storage']['step'] = 'upload';
                  
    break;
  }  
  
  if ($form_state['rebuild'] == FALSE && $form_state['executed'] == TRUE) {        
    $values = $form_state['values'] + $form_state['storage']['values'];
    $tid = db_result(db_query("SELECT tid FROM {term_data} WHERE name='%s' AND vid=%d", $values['breed'], VOCABULARY_BREED));    
    $existing = db_result(db_query("SELECT MIN(n.nid) FROM {node} AS n INNER JOIN {term_node} AS tn USING (nid, vid) WHERE tn.tid = %d AND LOWER(n.title)=LOWER('%s') AND n.uid=%d", $tid, $values['name'], $user->uid));
    if ($existing) {
      $node = node_load($existing);      
    } else {
      $node = new stdClass();
      $node->type = 'dog';    
      $node->title = $values['name'];
      $node->name = $user->name;
      $node->uid = $user->uid;
      $node->status = 1;
    }            
        
    foreach ($values['tilts'] as $fid => $file) {
      $node->field_image[] = $file;
      $tempfile = (object) $file;
      file_set_status($tempfile, 1);
    }      
    $node->caption = $values['caption'];        
    $node->field_breed[0]['value'] = $tid;          
    node_save($node);
    $form_state['nid'] = $node->nid;
  }
}

function theme_dtth_upload2_form($form) {
  if ($form['#parameters'][1]['storage']['step']) {
    $step = $form['#parameters'][1]['storage']['step'];
  } else {
    $step = 'default';        
  }
  $output = '';
  switch ($step) {
    case 'login':            
      $output = '<div id="upload_container" class="'.$step.'">
      '.drupal_render($form['signin_info']).'
      '.drupal_render($form['signin']).'
      </div>';
    break;
    case 'newbreed':
      $output = '<div id="upload_container" class="'.$step.'">
      <div class="upload_form_inputs">
      <div class="upload_form_input">'.drupal_render($form['newbreed_name']).'</div>      
      <div class="upload_form_btns container-inline">'.drupal_render($form['newbreed_submit']).drupal_render($form['newbreed_cancel']).'</div>      
      </div></div>';
    break;
    case 'upload':
      $output = '	<div id="crop_container" class="'.$step.'">
	    <div class="image_to_crop">
		'.drupal_render($form['tilt_focus_rect']) . drupal_render($form['tilt_image']).'
	    </div>
	    <div class="info">
		<p>
		    Drag the square around your pup to crop the image to a square.
		</p>
		<p>
		    <span class="tip">Tip:</span>
		    By cutting out the background you will be able to see your dog\'s head tilt more prominently. This may lead to high voting!
		</p>
		'.drupal_render($form['continue']).'
		    
	    </div>
	    <div class="clearfix"></div>
	</div>';
    break;
    case 'default':
      $output = '<div id="upload_container" class="'.$step.'">'.drupal_render($form['tilt_list']).'      	    
		<div class="upload_form_inputs">
		    
		    <div class="upload_form_input">
			<input id="edit-tilt-temp" type="text" name="" value="" placeholder="UPLOAD YOUR PUP TILTING! " />
		    </div>
		    <div class="upload_form_input">
			'.drupal_render($form['breed']).'
		    </div>
		    <div class="upload_form_input newbreed" style="display: none;">
			'.drupal_render($form['newbreed']).'
		    </div>
		    <div class="upload_form_input">
			'.drupal_render($form['name']).'
		    </div>
		    
		</div>
		
		<div class="upload_form_btns">
		    <div class="upload_browse" style="overflow: hidden">
			'.drupal_render($form['tilt']).'
		    </div>		    
		    '.drupal_render($form['upload']).'		    
		    
		</div>
		
		<div class="clearfix"></div>
		
		<div class="upload_form_inputs">
		    <div class="upload_form_input">
			'.drupal_render($form['caption']).'
		    </div>
		</div>
		
		<div class="upload_form_btns">
		    '.drupal_render($form['submit']).'
		</div>
		<div class="clearfix"></div>			    
	</div>';
    break;
  }
  $output .= '<div style="display: none">'.drupal_render($form).'</div>';  
	return $output;
}

function dtth_upload_breed_js($string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT tid, name FROM {term_data} WHERE LOWER(name) LIKE LOWER('%s%%') AND status=1", $string, 0, 10);
    while ($term = db_fetch_object($result)) {
      $matches[$term->name] = check_plain($term->name);
    }
  }
  $matches[t('Add New Breed')] = t('(Add New Breed)'); 

  drupal_json($matches);
}

function dtth_upload_check_directory(&$directory, $mode = 0, $form_item = NULL) {
  $directory = rtrim($directory, '/\\');

  // Check if directory exists.
  if (!is_dir($directory)) {
    if (($mode & FILE_CREATE_DIRECTORY) && @mkdir($directory)) {
      watchdog('dtth_upload',t('The directory %directory has been created.', array('%directory' => $directory)));
      @chmod($directory, 0775); // Necessary for non-webserver users.
    }
    else {
      if ($form_item) {
        form_set_error($form_item, t('The directory %directory does not exist.', array('%directory' => $directory)));
      }
      return FALSE;
    }
  }

  // Check to see if the directory is writable.
  if (!is_writable($directory)) {
    if (($mode & FILE_MODIFY_PERMISSIONS) && @chmod($directory, 0775)) {
      watchdog('dtth_upload', t('The permissions of directory %directory have been changed to make it writable.', array('%directory' => $directory)));
    }
    else {
      form_set_error($form_item, t('The directory %directory is not writable', array('%directory' => $directory)));
      watchdog('file system', 'The directory %directory is not writable, because it does not have the correct permissions set.', array('%directory' => $directory), WATCHDOG_ERROR);
      return FALSE;
    }
  }

  if ((file_directory_path() == $directory || file_directory_temp() == $directory) && !is_file("$directory/.htaccess")) {
    $htaccess_lines = "SetHandler Drupal_Security_Do_Not_Remove_See_SA_2006_006\nOptions None\nOptions +FollowSymLinks";
    if (($fp = fopen("$directory/.htaccess", 'w')) && fputs($fp, $htaccess_lines)) {
      fclose($fp);
      chmod($directory . '/.htaccess', 0664);
    }
    else {
      $variables = array(
        '%directory' => $directory,
        '!htaccess' => '<br />' . nl2br(check_plain($htaccess_lines)),
      );
      form_set_error($form_item, t("Security warning: Couldn't write .htaccess file. Please create a .htaccess file in your %directory directory which contains the following lines: <code>!htaccess</code>", $variables));
      watchdog('security', "Security warning: Couldn't write .htaccess file. Please create a .htaccess file in your %directory directory which contains the following lines: <code>!htaccess</code>", $variables, WATCHDOG_ERROR);
    }
  }

  return TRUE;
}