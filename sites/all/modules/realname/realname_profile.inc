<?php
/**
 * @file
 * Realname module support for Profile (core) module.
 */

/**
 * Implementation of hook_realname().
 */
function profile_realname() {
  return array(
    'name'   => 'Core Profile',
    'types'  => FALSE,
    'fields' => TRUE,
    'file'   => 'realname_profile.inc',
    'path'   => drupal_get_path('module', 'realname'),
  );
}

function profile_realname_get_fields($current) {
  $fields = $links = array();
  $result = db_query("SELECT name, type, title FROM {profile_fields}");
  while ($field = db_fetch_array($result)) {
    switch ($field['type']) {
      case 'selection':
      case 'textfield':
        $name = $field['name'];
        $selected = array_key_exists($name, (array) $current);
        $fields[$name] = array(
          'title' => $field['title'],
          'weight' => $selected ? $current[$name] : 0,
          'selected' => $selected,
          );
        break;

      case 'url':
        $links[$field['name']] = $field['title'];
        break;

      default:
        break;
    }
  }

  return array('fields' => $fields, 'links' => $links);
}
