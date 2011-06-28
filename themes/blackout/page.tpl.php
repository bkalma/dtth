<?php // $Id: page.tpl.php,v 1.1 2009/05/15 07:28:05 agileware Exp $ ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language ?>" lang="<?php print $language->language ?>" <?php if (isset($language->dir)) print 'dir="'.$language->dir.'"'; ?>>

  <head>
    <title><?php echo $head_title; ?></title>
    <?php echo $head; ?>
    <?php echo $styles; ?>
    <?php echo $scripts; ?>
    <!--[if IE 6]><link rel="stylesheet" href="<?php echo $base_path . $directory; ?>/style.ie6.css" type="text/css" /><![endif]-->
  </head>

  <body<?php print phptemplate_body_class($left, $right); ?>>
    <div id="header">
      <?php if ($site_name): ?>
        <h1><a href="<?php echo $base_path; ?>" title="<?php echo t('Home'); ?>"><?php echo($site_name); ?></a></h1>
      <?php endif; ?>
      <?php if ($site_slogan): ?>
        <h2><?php echo $site_slogan; ?></h2>
      <?php endif; ?>
    </div>
    <div id="menu">
      <div class="indent">
        <?php print theme('links', $primary_links); ?>
      </div>
    </div>
    <div id="page">
      <div id="container" class="clear-block">
        <?php if ($left): ?>
          <div id="sidebar-left" class="sidebar">
            <?php echo $left; ?>
          </div>
        <?php endif; ?>
        <div id="main">
          <div class="content-padding">
            <?php if ($mission): ?><div id="mission"><?php echo $mission; ?></div><?php endif; ?>
            <?php if ($breadcrumb): echo $breadcrumb; endif ?>
            <?php if ($tabs): ?><div class="tabs"><?php echo $tabs ?></div><?php endif; ?>
            <?php if ($title): ?><h1 class="title"><?php echo $title ?></h1><?php endif; ?>
            <?php echo $help; ?>
            <?php echo $messages; ?>
            <?php echo $content; ?>
            <?php echo $feed_icons; ?>
          </div>
        </div>
        <?php if ($right): ?>
          <div id="sidebar-right" class="sidebar">
            <?php echo $right; ?>
          </div>
        <?php endif; ?>
      </div>
      <div id="postcontent">
        <?php echo $footer ?>
        <div style="clear: both;"></div>
      </div>
      <div id="footer">
        <p><?php echo $footer_message; ?></p>
      </div>
      <?php print $closure; ?>
    </div>
  </body>
</html>