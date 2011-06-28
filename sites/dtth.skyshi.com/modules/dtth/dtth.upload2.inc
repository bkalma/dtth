<?php

function dtth_upload_ajax_start(&$form, &$form_state) {
  $form_state['title'] = t('Choose animal');

  $animals = dtth_upload_ajax_animals();
  foreach ($animals as $id => $animal) {
    $options[$id] = $animal['title'];
  }

  $form['type'] = array(
    '#title' => t('Choose your animal'),
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => $form_state['object']->type,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
}

function dtth_upload_ajax_cache_clear($id) {
  ctools_include('object-cache');
  ctools_object_cache_clear('ctools_ajax_sample', $id);
}

function dtth_upload_ajax_cache_get($id) {
  ctools_include('object-cache');
  $object = ctools_object_cache_get('ctools_ajax_sample', $id);
  if (!$object) {
    // Create a default object.
    $object = new stdClass;
    $object->type = 'unknown';
    $object->name = '';
  }

  return $object;
}

function ctools_upload_ajax_cache_set($id, $object) {
  ctools_include('object-cache');
  ctools_object_cache_set('ctools_ajax_sample', $id, $object);
}


function dtth_upload_ajax_animals() {
  //return array();
  return array(
    'sheep' => array(
      'title' => t('Sheep'),
      'config title' => t('Configure sheep'),
      'form' => 'ctools_ajax_sample_configure_sheep',
      'output' => 'ctools_ajax_sample_show_sheep',
    ),
    'lizard' => array(
      'title' => t('Lizard'),
      'config title' => t('Configure lizard'),
      'form' => 'ctools_ajax_sample_configure_lizard',
      'output' => 'ctools_ajax_sample_show_lizard',
    ),
    'raptor' => array(
      'title' => t('Raptor'),
      'config title' => t('Configure raptor'),
      'form' => 'ctools_ajax_sample_configure_raptor',
      'output' => 'ctools_ajax_sample_show_raptor',
    ),
  );
}

function dtth_upload_wizard_next(&$form_state) {
  ctools_upload_ajax_cache_set($form_state['object_id'], $form_state['object']);
}


function dtth_upload2_page() {
  $form_info = array(
    'id' => 'animals',
    'path' => 'upload2',
    'show trail' => TRUE,
    'show back' => TRUE,
    'show cancel' => TRUE,
    'show return' => FALSE,
    'next callback' =>  'dtth_upload_wizard_next',
    //'finish callback' => 'ctools_ajax_sample_wizard_finish',
    //'cancel callback' => 'ctools_ajax_sample_wizard_cancel',
   // this controls order, as well as form labels
    'order' => array(
      'start' => t('Choose animal'),
    ),
   // here we map a step to a form id.
    'forms' => array(
      // e.g. this for the step at wombat/create
      'start' => array(
        'form id' => 'dtth_upload_ajax_start'
      ),
    ),
  );
                                                                         
  // We're not using any real storage here, so we're going to set our
  // object_id to 1. When using wizard forms, id management turns
  // out to be one of the hardest parts. Editing an object with an id
  // is easy, but new objects don't usually have ids until somewhere
  // in creation.
  //
  // We skip all this here by just using an id of 1.

  $object_id = 1;

  if (empty($step)) {
    // We reset the form when $step is NULL because that means they have
    // for whatever reason started over.
    dtth_upload_ajax_cache_clear($object_id);
    $step = 'start';
  }

  // This automatically gets defaults if there wasn't anything saved.
  $object = dtth_upload_ajax_cache_get($object_id);

  $animals = dtth_upload_ajax_animals();  

  // Make sure we can't somehow accidentally go to an invalid animal.
  if (empty($animals[$object->type])) {
    $object->type = 'unknown';
  }

  // Now that we have our object, dynamically add the animal's form.
  if ($object->type == 'unknown') {
    // If they haven't selected a type, add a form that doesn't exist yet.
    $form_info['order']['unknown'] = t('Configure animal');
    $form_info['forms']['unknown'] = array('form id' => 'nothing');
  }
  else {
    // Add the selected animal to the order so that it shows up properly in the trail.
    $form_info['order'][$object->type] = $animals[$object->type]['config title'];
  }

  // Make sure all animals forms are represented so that the next stuff can
  // work correctly:
  foreach ($animals as $id => $animal) {
  //  $form_info['forms'][$id] = array('form id' => $animals[$id]['form']);
  }

  $form_state = array(
    'ajax' => $js,
    // Put our object and ID into the form state cache so we can easily find
    // it.
    'object_id' => $object_id,
    'object' => &$object,
  );

  // Send this all off to our form. This is like drupal_get_form only wizardy.
  ctools_include('wizard');
  $output = ctools_wizard_multistep_form($form_info, $step, $form_state);

  if ($output === FALSE || !empty($form_state['complete'])) {
    // This creates a string based upon the animal and its setting using
    // function indirection.
    $animal = $animals[$object->type]['output']($object);
  }

  // If $output is FALSE, there was no actual form.  
    // If javascript is active, we have to use a render array.
    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // Dismiss the modal.
      $commands[] = ctools_ajax_command_html('#ctools-sample', $animal);
      $commands[] = ctools_modal_command_dismiss();
    }
    else if (!empty($form_state['cancel'])) {
      // If cancelling, return to the activity.
      $commands[] = ctools_modal_command_dismiss();
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    ctools_ajax_render($commands);  
}