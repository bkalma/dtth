<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>
  <?php print $scripts ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
</head>
<body>
<div id="main_container">
  <div id="header">
    <div id="logo"><?php if ($logo) { ?><a href="<?php print $base_path ?>" title="<?php print t('Skyshi - Drupal Development Services') ?>"><img src="<?php print $logo ?>" alt="<?php print t('Skyshi - Drupal Development Services') ?>" /></a><?php } ?></div>
    <div id="menu">
			<?php if (isset($primary_links)) { ?><?php print theme('links', $primary_links) ?><?php } ?>
    </div>
  </div>
  <div id="middle_box">
    <div class="middle_box_content">
    	<?php print $header ?>
    </div>
  </div>
  <div id="center_content">
    <div class="left_content">
      <div class="title_photos">My portfolios</div>
      	<?php print $portofolio ?>
      <div class="title_photos">My friends</div>
      <div class="friends_list">
        <?php print $left ?>
      </div>
    </div>
    <div class="right_content">
      <div class="title_journal">My journal</div>
        <?php print $breadcrumb ?>
        <h1 class="title"><?php print $title ?></h1>
        <div class="tabs"><?php print $tabs ?></div>
        <?php print $help ?>
        <?php print $messages ?>
        <?php print $content; ?>
    </div>
    <div class="clear"></div>
  </div>
  <div id="footer">
    <div class="copyright"><?php print $footer_message ?></div>
    <div class="footer_links"><?php print $footer ?></div>
  </div>
</div>
<?php print $closure ?>
</body>
</html>
