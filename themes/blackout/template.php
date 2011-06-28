<?php
// $Id: template.php,v 1.1 2009/05/15 07:28:05 agileware Exp $

function phptemplate_body_class($left, $right) {
  if ($left && $right) {
    $class = 'sidebars-2';
  }
  else if ($left || $right) {
    $class = 'sidebars-1';
  }
  if(isset($class)) {
    print ' class="' . $class . '"';
  }
}

function blackout_feed_icon($url, $title) {
  if ($image = theme('image', path_to_theme() . '/images/feed.png', t('Syndicate content'), $title)) {
    return '<a href="' . check_url($url) . '" class="feed-icon">' . $image . '</a>';
  }
}