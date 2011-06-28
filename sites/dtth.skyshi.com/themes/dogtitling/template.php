<?php

function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    /*$active_trail = menu_get_active_trail();
    $links = array();
    $class_last = '';        
    //$active_trail[] = array(
      //'title' => drupal_get_title(),
      //'href' => $_GET['q'],
    //);         
    $num_links = count($active_trail);
    foreach ($active_trail as $key => $link) {
      if ($num_links - 1 == $key) {
        $class_last = 'last_node';
        $last_link = l($link['title'], $link['href'], array('attributes' => array('class' => $class_last)));
      } else {
        $links[] = l($link['title'], $link['href'], array('attributes' => array('class' => 'node ' . $class_last)));
      }                          
    } */   
    $links = drupal_get_breadcrumb();
    $num_links = count($links);
    if ($num_links > 1) {
      $last_link = array_pop($links);      
      return '<nav id="breadcrumb">' . implode('<a class="separator" href="">&nbsp;</a>', $links) .
      $last_link . 
      '<a class="last_node_corner" href="">&nbsp;</a></nav>';
    }
  }
}

function phptemplate_links_custom($links, $attributes = array('class' => 'links'), $attributes_links = array()) {
  global $language;
  $output = '';

  if (count($links) > 0) {
    $output = '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = $key;

      // Add first, last and active classes to the list of links to help out themers.
      if ($i == 1) {
        $class .= ' first';
      }
      if ($i == $num_links) {
        $class .= ' last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
           && (empty($link['language']) || $link['language']->language == $language->language)) {
        $class .= ' active';
      }
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['title'], $link['href'], $link);
      }
      else if (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

function phptemplate_menu_primary_links() {
  $primary_links = menu_primary_links();
  foreach ($primary_links as $key => $value) {
    $primary_links[$key]['attributes']['class'] = 'png_bg';
  }  
  print_r($primary_links);
  return theme('links', $primary_links, array('class' => 'top_nav')); 
}

function phptemplate_menu_local_tasks() {
  $output = '';

  if ($primary = menu_primary_local_tasks()) {
    $output .= "<ul class=\"borderradius\">\n" . $primary . "</ul>\n";
  }  

  return $output;
}


function phptemplate_item_list($items = array(), $title = NULL, $type = 'ul', $attributes = NULL) {
  //$output = '<div class="item-list">';
  if (isset($title)) {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    foreach ($items as $i => $item) {
      $attributes = array();
      $children = array();
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        $data .= theme_item_list($children, NULL, $type, $attributes); // Render nested list
      }
      if ($i == 0) {
        $attributes['class'] = empty($attributes['class']) ? 'first' : ($attributes['class'] . ' first');
      }
      if ($i == $num_items - 1) {
        $attributes['class'] = empty($attributes['class']) ? 'last' : ($attributes['class'] . ' last');
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  //$output .= '</div>';
  return $output;
}
/*
function phptemplate_preprocess_rate_template_thumbs_up(&$variables) {
  extract($variables);
  
  print 'okokokok';  

  $variables['up_button'] = theme('rate_button', $links[0]['text'], $links[0]['href'], 'like rate-thumbs-up-btn-up');

  $info = array();
  if ($mode == RATE_CLOSED) {
    $info[] = t('Voting is closed.');
  }
  if ($mode != RATE_COMPACT && $mode != RATE_COMPACT_DISABLED) {
    if ($results['user_vote']) {
      //$info[] = format_plural($results['count'], 'Only you voted.', '@count users have voted, including you.');
      $info[] = $results['count'];
    }
    else {
      //$info[] = format_plural($results['count'], '@count user has voted.', '@count users have voted.');
      $info[] = $results['count'];
    }
  }
  $variables['info'] = implode(' ', $info);
}
*/

function phptemplate_quicktabs_tabs($quicktabs, $active_tab = 'none') {
  if ($quicktabs['machine_name'] == 'topvotedcaptions') {
    return phptemplate_quicktabs_tabs_topvotedcaptions($quicktabs, $active_tab);
  }  
  $output = '';
  $tabs_count = count($quicktabs['tabs']);
  if ($tabs_count <= 0) {
    return $output;
  }

  $index = 1;
  $output .= '<ul class="quicktabs_tabs quicktabs-style-'. drupal_strtolower($quicktabs['style']) .'">';
  foreach ($quicktabs['tabs'] as $tabkey => $tab) {
    $class = 'qtab-'. $tabkey;
    // Add first, last and active classes to the list of tabs to help out themers.
    $class .= ($tabkey == $active_tab ? ' active' : '');
    $class .= ($index == 1 ? ' first' : '');
    $class .= ($index == $tabs_count ? ' last': '');
    $attributes_li = drupal_attributes(array('class' => $class));
    $options = _quicktabs_construct_link_options($quicktabs, $tabkey);
    // Support for translatable tab titles with i18nstrings.module.
    if (module_exists('i18nstrings')) {
      $tab['title'] = tt("quicktabs:tab:$quicktabs[machine_name]--$tabkey:title", $tab['title']);
    }
    $output .= '<li'. $attributes_li .'>'. l($tab['title'], $_GET['q'], $options) .'</li>';
    $index++;
  }
  $output .= '</ul>';
  return $output;
}


function phptemplate_quicktabs_tabs_topvotedcaptions($quicktabs, $active_tab = 'none') {
  
  $output = '';
  $tabs_count = count($quicktabs['tabs']);
  if ($tabs_count <= 0) {
    return $output;
  }

  $index = 1;
  $output .= '<nav id="sidebar_tab" class="tabs">';
  $output .= '<ul class="borderradius sidebar_tabs quicktabs_tabs quicktabs-style-'. drupal_strtolower($quicktabs['style']) .'">';
  foreach ($quicktabs['tabs'] as $tabkey => $tab) {
    $class = 'qtab-'. $tabkey;
    // Add first, last and active classes to the list of tabs to help out themers.
    $class .= ($tabkey == $active_tab ? ' active' : '');
    $class .= ($index == 1 ? ' first' : '');
    $class .= ($index == $tabs_count ? ' last': '');
    $attributes_li = drupal_attributes(array('class' => $class));
    $options = _quicktabs_construct_link_options($quicktabs, $tabkey);
    // Support for translatable tab titles with i18nstrings.module.
    if (module_exists('i18nstrings')) {
      $tab['title'] = tt("quicktabs:tab:$quicktabs[machine_name]--$tabkey:title", $tab['title']);
    }
    $output .= '<li'. $attributes_li .'>'. l($tab['title'], $_GET['q'], $options) .'</li>';
    $index++;
  }
  $output .= '</ul>';
  $output .= '</nav>';
  return $output;
}


function phptemplate_content_multiple_values($element) {
  $field_name = $element['#field_name'];
  $field = content_fields($field_name);
  $output = '';

  if ($field['multiple'] >= 1) {
    $table_id = $element['#field_name'] .'_values';
    $order_class = $element['#field_name'] .'-delta-order';
    $required = !empty($element['#required']) ? '<span class="form-required" title="'. t('This field is required.') .'">*</span>' : '';

    $header = array(
      array(
        'data' => t('!title: !required', array('!title' => $element['#title'], '!required' => $required)),
        'colspan' => 2
      ),
      t('Order'),
    );
    $rows = array();

    // Sort items according to '_weight' (needed when the form comes back after
    // preview or failed validation)
    $items = array();
    foreach (element_children($element) as $key) {
      if ($key !== $element['#field_name'] .'_add_more') {
        $items[] = &$element[$key];
      }
    }
    usort($items, '_content_sort_items_value_helper');

    // Add the items as table rows.
    foreach ($items as $key => $item) {
      $item['_weight']['#attributes']['class'] = $order_class;
      $delta_element = drupal_render($item['_weight']);
      $cells = array(
        array('data' => '', 'class' => 'content-multiple-drag'),
        drupal_render($item),
        array('data' => $delta_element, 'class' => 'delta-order'),
      );
      $rows[] = array(
        'data' => $cells,
        'class' => 'draggable',
      );
    }

    //$output .= theme('table', $header, $rows, array('id' => $table_id, 'class' => 'content-multiple-table'));
    $output .= theme('table', NULL, $rows, array('id' => $table_id, 'class' => 'content-multiple-table'));
    $output .= $element['#description'] ? '<div class="description">'. $element['#description'] .'</div>' : '';
    $output .= drupal_render($element[$element['#field_name'] .'_add_more']);

    drupal_add_tabledrag($table_id, 'order', 'sibling', $order_class);
  }
  else {
    foreach (element_children($element) as $key) {
      $output .= drupal_render($element[$key]);
    }
  }

  return $output;
}