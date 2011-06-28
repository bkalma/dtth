<?php

function dtth_upload_page() {
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
    $form_id = $node->type . '_node_form';
    $form_state = array(
      'title' => t('Login'),
      'ajax' => TRUE,
      'args' => array($node),
    );
                      
    $content = ctools_modal_form_wrapper($form_id, $form_state);        
    if (empty($content)) {          
      // empty $output signifies success, so we'll use it as our $commands
      // array.
      $redirect = explode("/", $form_state['redirect']);
      $nid = $redirect[1];
      $content = array();
      $content[] = ctools_modal_command_loading();
      //$content[] = ctools_ajax_command_redirect($form_state['redirect']);
      $node = node_load($nid);
      $title = $node->title;
      $output = node_view($node, FALSE, FALSE);
      $content[] = ctools_modal_command_display($title, $output);
      $content[] = ctools_ajax_command_css('#modalContent .pre_post_box_action .fb', array('position' => 'relative'));
      //$content[] = ctools_ajax_command_eval('$(\'#modalContent .node_'.$node->nid.' a.fb\').attr(\'title\',\'Share on Facebook or Twitter\').tooltip({api: true}).show();');
      //$content[] = ctools_ajax_command_eval('$(\'#modalContent .node_'.$node->nid.' a.fb\').attr(\'title\',\'Share on Facebook or Twitter\');');
      /*$content[] = ctools_ajax_command_append('#modalContent .pre_post_box_action .fb', '<div class="ballon" style="position: absolute; left: -80px;">
<div class="ballon_inner">Congrats! Your best friend is on the path to fame! With a little help from Facebook and Twitter fame could be even closer than you think!</div></div>');*/      
    }
    ctools_ajax_render($content);
  } else {
    $content = drupal_get_form($node->type . '_node_form', $node);
    modalframe_child_js();
    return $content;
  }
}
/*
function dtth_upload_page() {
  global $user;
  ctools_include('node.pages', 'node', '');
  $GLOBALS['dtth_upload_page'] = TRUE;
  $node = new stdClass();
  $node->type = 'dog';  
  $node->uid = $user->uid;
  $node->name = $user->name;  
  $output = drupal_get_form($node->type . '_node_form', $node);
  return $output;
}*/

function dtth_upload_tilt_page() {
  return drupal_get_form('dtth_upload_tilt_form');
}

function dtth_upload_tilt_form($form, &$form_state) {
  $form = array();
  $form['#prefix'] = '<div class="container-inline">';
  $form['image'] = array(
    '#type' => 'file',    
  );
  $form['upload'] = array(
    '#type' => 'submit',
    '#value' => t('Upload'),
    '#ahah' => array(
      'path' => 'upload/tilt/js',
      'wrapper' => 'tilt_wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),    
  );
  $form['wrapper'] = array(
    '#type' => 'markup',
    '#value' => '<div class="tilt_wrapper"></div>',    
  );  
  $form['#suffix'] = '</div>';
  return $form;
}

function dtth_upload_tilt_js() {
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
  // This call recreates the form relying solely on the form_state that the
  // drupal_process_form set up.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
  // Render the new output.
  $wrapper = $form['wrapper'];
  unset($wrapper['#prefix'], $wrapper['#suffix']); // Prevent duplicate wrappers.
  $output = theme('status_messages') . drupal_render($wrapper);

  drupal_json(array('status' => TRUE, 'data' => $output));
}

/*function dtth_upload_tilt_page($form_id) {
  global $user;
  ctools_include('node.pages', 'node', '');
  $GLOBALS['dtth_upload_page'] = TRUE;
  $node = new stdClass();
  $node->type = 'tilt';
  $node->title = 'test';  
  $node->uid = $user->uid;
  $node->name = $user->name;  
  $output = drupal_get_form($node->type . '_node_form', $node);
  return $output;
}*/

function dtth_upload_new($node) {
  $node->viewpage = 'recent';
  $output .= node_view($node, FALSE, FALSE);
  
}

function dtth_browse_recent($js = NULL) {  
  $page = $_GET['page'];
  $limit = 10;
  $result = db_query_range("SELECT n.nid FROM {node} AS n INNER JOIN {term_node} AS tn ON  n.nid = tn.nid INNER JOIN {term_data} AS td ON td.tid = tn.tid WHERE n.type='tilt' AND td.status = 1 ORDER BY n.created DESC", NULL, $limit * $page, $limit);
  $items = array();
  $i = 0;  
  $output = '';
  while ($item = db_fetch_object($result)) {
    $node = node_load($item->nid);
    $node->viewpage = 'recent';
    $output .= node_view($node, FALSE, FALSE);
    $i++;  
  }
    
  //$output .= theme('pager', NULL, $limit);
    
  // only display more button if there is still more content (or indicated by $i still equal $limit)
  if ($i == $limit) {
    $q['page'] = $page + 1;
    $output .= l(t('More'), 'browse/recent/js', array('query' => $q, 'attributes' => array('class' => 'ctools-use-ajax more-button')));
  }
  
  if (!$js) {
    return $output;
  } else {
    ctools_include('ajax');
    $commands = array();
    $commands[] = ctools_ajax_command_remove('.post_boxes .more-button');
    $commands[] = ctools_ajax_command_append('.post_boxes', $output);
    ctools_ajax_render($commands); // this function exits.
  }
}

function dtth_browse_breed() {
  $limit = 8;
  $vid = VOCABULARY_BREED;
  $result = db_query("SELECT tid, name, tilt_total FROM {term_data} WHERE vid=%d AND status=1 ORDER BY name", $vid);
  $items = array();
  $tables = array();
  $output = '';      
  $i = 0;  
  while ($item = db_fetch_object($result)) {
    $output2 = '';
    if ($i % 2 == 0) {
    $output2 .= '<div class="breed_lists_box breed_lists_box_odd">';
    } else {
    $output2 .= '<div class="breed_lists_box breed_lists_box_even">';
    }        
    $result2 = db_query_range("SELECT n.nid FROM {node} AS n INNER JOIN {term_node} AS t ON n.vid = t.vid WHERE n.type = 'tilt' AND t.tid=%d ORDER BY n.created DESC", $item->tid, 0, $limit);
    //$result2 = db_query_range("SELECT n.nid FROM {node} AS n INNER JOIN {term_node} AS t ON n.vid = t.vid INNER JOIN {term_data} AS td ON td.tid = t.tid WHERE n.type = 'tilt' AND t.tid=%d ORDER BY td.name ASC", $item->tid, 0, $limit);    
    $output2 .= '<h3 class="breed_lists_box_title">'.l($item->name, 'browse/breed/'. $item->tid).'</h3>';
    $output2 .= '<div class="breed_lists_box_thumbs">';
    $node = NULL;
    while ($item2 = db_fetch_object($result2)) {
      $node = node_load($item2->nid);            
      $output2 .= l(theme('imagecache', 'browse_breed',$node->field_image[0]['filepath']), 'node/'. $node->nid, array('html' => TRUE));             
    }          
    $output2 .= '<div class="clearfix"></div>';
    $output2 .= '</div>';    
    $output2 .= l(t('View All !tilt_total Head Tilt\'s', array('!tilt_total' => $item->tilt_total)), 'browse/breed/'.$item->tid, array('attributes' => array('class' => 'view_all_breed')));
    $output2 .= '</div>';        
    
    if ($node) {
      $output .= $output2;
      $i++;
    }
  }    
  
  return $output;
}

function dtth_browse_favorite($js = NULL) {
  $output = '';
  $limit = 10;
  $page = $_GET['page'];
  //$criteria['content_type'] = 'comment';
  $criteria['value_type'] = 'points';
  $criteria['tag'] = 'vote';
  $criteria['function'] = 'count';
  //$criteria['timestamp'] = (time() - (7*24*60*60));
  $table = 'cache';
  $query = "SELECT * FROM {votingapi_" . $table . "} v   
  INNER JOIN {node} AS n ON n.nid = v.content_id AND v.content_type='node' AND n.type='tilt'    
  WHERE 1 = 1";
  $details = _votingapi_query('vote', $criteria);
  $query .= $details['query'];        
  $query .= " ORDER BY v.value DESC";                  
  $result = db_query_range($query, $details['args'], $page * $limit, $limit);  
  $items = array();
  $i = 0;
  while ($item = db_fetch_object($result)) {
    $node = node_load($item->nid);
    $node->viewpage = 'recent';
    $output .= node_view($node, FALSE, FALSE);
    $i++;  
  }  
    
  // only display more button if there is still more content (or indicated by $i still equal $limit)
  if ($i == $limit) {
    $q['page'] = $page + 1;
    $output .= l(t('More'), 'browse/favorite/js', array('query' => $q, 'attributes' => array('class' => 'ctools-use-ajax more-button')));
  }
  
  if (!$js) {
    return $output;
  } else {
    ctools_include('ajax');
    $commands = array();
    $commands[] = ctools_ajax_command_remove('.post_boxes .more-button');
    $commands[] = ctools_ajax_command_append('.post_boxes', $output);
    ctools_ajax_render($commands); // this function exits.
  }
  
  return $output;
}

function dtth_browse_frequent($js = NULL) {
  $limit = 10;
  $page = $_GET['page'];  
  $query = "SELECT n.nid FROM {node} AS n INNER JOIN {content_type_dog} AS d ON n.vid = d.vid WHERE n.type='dog' AND n.status=1 ORDER BY d.field_tilt_total_value DESC, n.created DESC";                  
  $result = db_query_range($query, NULL, $page * $limit, $limit);
  $items = array();
  $i = 0;  
  $output = '';
  while ($item = db_fetch_object($result)) {
    $node = node_load($item->nid);
    $node->viewpage = 'frequent';
    $output .= node_view($node, FALSE, FALSE);
    $i++;  
  }
  
    // only display more button if there is still more content (or indicated by $i still equal $limit)
  if ($i == $limit) {
    $q['page'] = $page + 1;
    $output .= l(t('More'), 'browse/frequent/js', array('query' => $q, 'attributes' => array('class' => 'ctools-use-ajax more-button')));
  }
    
  if (!$js) {    
    return $output;
  } else {
    ctools_include('ajax');
    $commands = array();
    $commands[] = ctools_ajax_command_remove('.post_boxes .more-button');
    $commands[] = ctools_ajax_command_append('.post_boxes', $output);
    ctools_ajax_render($commands); // this function exits.
  }
}

function dtth_browse_breed_detail($tid) {
  $limit = 10;        
  
  $term = taxonomy_get_term($tid);          
  
  $output = '<div class="pre_post_box">';
  $output .= '<div class="pre_post_box_entry">';
  $term_link = l($term->name, 'browse/breed/'.$tid);
  $message = t('!term_link have tilted their heads !tilt_total times', array('!term_link' => $term_link, '!tilt_total' => $term->tilt_total));
  
  drupal_set_html_head('<meta property="og:title" content="'.strip_tags($message).'" />');
  drupal_set_html_head('<meta property="og:description" content="'.strip_tags($message).'" />');
  
  $output .= $message;  
  $output .= '</div>';
  $output .= '<div class="pre_post_box_action">'.dtth_share('facebook').dtth_share('twitter', NULL, FALSE, strip_tags($message)).'</div>';
  $output .= '</div>';
  $output .= '<div class="clearfix"></div>';
  $output .= '<div class="breed_boxes">';
  $result = pager_query("SELECT n.nid FROM {node} AS n INNER JOIN {term_node} AS t ON n.nid = t.nid AND n.vid = t.vid WHERE n.type='dog' AND t.tid=%d ORDER BY n.created DESC", $limit, NULL, NULL, $tid);
  $items = array();
    while ($item = db_fetch_object($result)) {    
    $node = node_load($item->nid);
    $node->viewpage = 'breeddetail';
    $output .= node_view($node, FALSE, FALSE);
    $i++;      
  }
  $output .= '</div>';
    
  $output .= theme('pager', NULL, $limit);
  
  return $output;
}