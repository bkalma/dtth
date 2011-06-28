<?php

function dtth_caption_detail_page($node, $caption) {
  $node->viewpage = 'caption';          
  $output = node_view($node);    
  
  // get comment
  $nid = $node->nid;
  $cid = $caption;
  $query = "SELECT c.cid as cid, c.pid, c.nid, c.subject, c.comment, c.format, c.timestamp, c.name, c.mail, c.homepage, u.uid, u.name AS registered_name, u.signature, u.signature_format, u.picture, u.data, c.thread, c.status FROM {comments} c INNER JOIN {users} u ON c.uid = u.uid LEFT JOIN {votingapi_cache} AS v ON c.cid = v.content_id AND v.content_type='comment' AND v.function='count' AND v.value_type='points' WHERE c.nid = %d AND c.cid = %d AND c.status=0";
  $query_args = array($nid, $cid);
  $comment = db_fetch_object(db_query($query, $query_args));  
  
  drupal_set_html_head('<meta property="og:title" content="'.$comment->comment.'" />');
  drupal_set_html_head('<meta property="og:description" content="'.$comment->comment.'" />');
  $imagecache_url = imagecache_create_url('normal', $node->field_image[0]['filepath']);                                        
  drupal_set_html_head('<meta property="og:image" content="'.$imagecache_url.'" />');
  drupal_set_html_head('<meta property="og:url" content="'.url('node/'.$node->nid, array('absolute' => TRUE)).'" />');
  
  drupal_set_title($comment->comment);
  
  drupal_add_js(drupal_get_path('module','dtth') . '/js/jquery.localscroll.js');
  drupal_add_js(drupal_get_path('module','dtth') . '/js/jquery.scrollTo.js');
  drupal_add_js("
function caption_scroll() {
  $.scrollTo('.node_".$node->nid."  .view_caption_ajax .captions .caption_".$cid."', 1000, { easing:'linear' });
}
    
Drupal.behaviors.caption = function(context) {
  $('a.add_caption').trigger('click');
  setTimeout('caption_scroll()', 800);  
}",'inline');
  
  return $output;
}

function dtth_caption_submit($node) {
  $commands = array();
    
  $form_state = array(
    'storage' => NULL,
    'submitted' => FALSE,
  );
  $form_build_id = $_POST['form_build_id'];
  // Get the form from the cache.
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  // We will run some of the submit handlers so we need to disable redirecting.
  $form['#redirect'] = FALSE;
  // We need to process the form, prepare for that by setting a few internals
  // variables.
  $form['#post'] = $_POST;
  $form['#programmed'] = FALSE;
  $form_state['post'] = $_POST;
  // Build, validate and if possible, submit the form.
  drupal_process_form($form_id, $form, $form_state);  
    
  $commands[] = ctools_ajax_command_append('.node_'.$node->nid.'  .view_caption_ajax .captions', $output);
  ctools_ajax_render($commands);
}

function dtth_caption_list_page($node, $js = TRUE) {  
  //$output = '<h1>' . t('Hello World') . '</h1>';
  if ($js) {
                                                   
    $node = node_build_content($node, TRUE, TRUE);
        
    ctools_include('ajax');
    $commands = array();
    //$output = '<div class="caption_box">'.comment_form_box(array('nid' => $node->nid)). '</div>';
    
    $form_state = array(
      'title' => t('Login'),       
      'args' => array(
        array('nid' => $node->nid),
      ),
      'ajax' => TRUE,
      're_render' => FALSE,
      'no_redirect' => TRUE,                 
    );    
    $form_id = 'dtth_caption_form';
    
    //$output = '<div class="caption_box">'.comment_form_box(array('nid' => $node->nid)). '</div>';
    $output = '<div class="caption_box">'.ctools_build_form($form_id, $form_state). '</div>';
    //$output .= '<div class="captions">' . dtth_comment_render($node) . '</div>';
    $output .= '<div class="captions">' . $node->content['comment']['#value'] . '</div>';
    
    $commands[] = ctools_ajax_command_html('.node_'.$node->nid.' .view_caption_ajax', $output);
    //$commands[] = ctools_ajax_command_eval('$.localScroll({target: "#captions"});');
    //$commands[] = ctools_ajax_command_eval('alert("hello");');
    //$commands[] = ctools_ajax_command_eval('$.scrollTo(\'.node_'.$node->nid.'  .view_caption_ajax\', 500, { easing:\'linear\' });');
    $commands[] = ctools_ajax_command_eval('var node_'.$node->nid.' = 0;');
    $commands[] = ctools_ajax_command_eval('$(\'.node_'.$node->nid.'  .view_caption_ajax\').slideToggle(\'slow\', function() {
      if ($(this).css(\'display\') == \'block\') {        
        $(\'.node_'.$node->nid.'  .add_caption\').addClass(\'open\');
      } else {
        $(\'.node_'.$node->nid.'  .add_caption\').removeClass(\'open\');
      };
    });;');                            
    /*$commands[] = ctools_ajax_command_eval('
    $("#comment-form").ajaxForm(function() {
      
    });');*/
    ctools_ajax_render($commands); // this function exits.
  }
  else {
    return $output;;
  }
}

function dtth_caption_form(&$form_state, $edit, $title = NULL) {
  global $user;
  
  $form = array();  
  
   // since when user changed, session will be destroyed, then we need to restore form state storage from cache 
  if ($_POST['op'] == t('Login')) {
    $form_build_id = $_POST['form_build_id'];    
    if ($cached = cache_get('storage_' . $form_build_id, 'cache_form')) {      
      $form_state['storage'] = $cached->data;
    } 
  } 
  
  // $form['#post'] is needed because http://drupal.org/node/678158#comment-2584406  
  $form['#attributes'] = array('enctype' => "multipart/form-data");
  $form['#post'] = array();
  
  $form['#prefix'] = '<div class="caption_message"></div><div class="caption_add">';
  $form['#suffix'] = '</div>';
  $form['comment'] = array(
    '#type' => 'textarea',     
    '#rows' => 15, 
    '#default_value' => '',     
    '#resizable' => FALSE,    
    '#attributes' => array(
      'class' => 'caption_text counter',
      'maxlength' => 120,
      'placeholder' => t('What\'s going through this dog\'s mind? Tell us! PS, it\'ll probably make for a great tweet!'),
    ),
  );  
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $edit['nid'],
  );  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 19,
    '#attributes' => array(
      'class' => 'post_btn ctools-use-ajax',
    ),
  );
  
  if (!(bool) $user->uid) {
    $form['submit2'] = array(
      '#type' => 'markup',
      '#value' => ctools_modal_text_button(t('Signin'), 'signin', t('Signin'), 'post_btn ctools-modal-ctools-sample-style'),
    );
    $form['submit']['#attributes']['class'] = 'post_btn ctools-use-ajax';
    $form['submit']['#attributes']['style'] = 'display: none;';
  }

  return $form;
}

function dtth_caption_form_validate($form, &$form_state) {
  global $user;
  
  $values = $form_state['values'];  
  $node = node_load($form_state['values']['nid']);
  $output = '';
  
  if ($values['op'] == t('Save') && $values['comment'] && strlen($values['comment']) > 120) {
    $output = t('Maximum caption should be lower than 120 characters');        
  }  
  if ($values['op'] == t('Save') && empty($values['comment'])) {
    $output = t('Please fill caption');
  }
  
  $commands = array();
  if (!empty($output)) {
    $commands[] = ctools_ajax_command_html('.node_'.$node->nid.' .view_caption_ajax .caption_message', $output);    
    $commands[] = ctools_ajax_command_eval('$(".node_'.$node->nid.' .view_caption_ajax .caption_message").attr("class","caption_message")');    
    $commands[] = ctools_ajax_command_eval('$(".node_'.$node->nid.' .view_caption_ajax .caption_message").addClass("error")');
    ctools_ajax_render($commands);
    form_set_error('comment', $output);
  }
}

function dtth_caption_form_submit($form, &$form_state) {
  global $user;
  $values = $form_state['values'];
  if ($values['op'] == t('Save') && $values['comment']) {
    $form_state['values']['author'] = $user->name;
    _comment_form_submit($form_state['values']);
    if ($cid = comment_save($form_state['values'])) {    
      $node = node_load($form_state['values']['nid']);
      $node = node_build_content($node, TRUE, TRUE);
      // Add 1 to existing $node->comment count to include new comment being added.
      $comment_count = $node->comment_count + 1;
      $page = comment_new_page_count($comment_count, 1, $node);
      $output = dtth_comment_render($node, $cid);
      $commands[] = ctools_ajax_command_eval('$(".node_'.$node->nid.' textarea.caption_text").val("");');          
      $commands[] = ctools_ajax_command_append('.node_'.$node->nid.'  .view_caption_ajax .captions', $output);
      //$commands[] = ctools_ajax_command_eval('$.scrollTo(\'.node_'.$node->nid.'  .view_caption_ajax .captions .caption_'.$cid.'\', 1000, { easing:\'linear\' });');
      $commands[] = ctools_ajax_command_html('.node_'.$node->nid.' .view_caption_ajax .caption_message', '');
      $commands[] = ctools_ajax_command_eval('$(".node_'.$node->nid.' .view_caption_ajax .caption_message").attr("class","caption_message")');        
      ctools_ajax_render($commands);
    }  
  }
}