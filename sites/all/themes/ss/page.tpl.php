<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>
  <?php print $scripts ?>
</head>
<body>
<div id="wrapper">
	<div id="header">
		<div id="logo">
			<?php if ($site_name) { ?><h1><a href="<?php print $base_path ?>" title="<?php print t('Home') ?>"><?php print $site_name ?></a></h1><?php } ?>
			<?php if ($site_slogan) { ?><p><?php print $site_slogan ?></p><?php } ?>
		</div>
	</div>
	<!-- end #header -->
	<div id="menu">
		<?php if (isset($primary_links)) { ?><?php print theme('links', $primary_links, array('class' =>'links')) ?><?php } ?>
	</div>
	<!-- end #menu -->
	<div id="page">
		<div id="content">
			<?php if ($header) { ?><div id="banner"><?php print $header ?></div><?php } ?>
			<div class="post">
					<h1 class="title"><?php print $title ?></h1>
	        <div class="tabs"><?php print $tabs ?></div>
	        <?php print $help ?>
	        <?php print $messages ?>
	        <?php print $content; ?>
			</div>
			<div style="clear: both;">&nbsp;</div>
		</div>
		<!-- end #content -->
		<div id="sidebar">
			<ul>
				<li>
					<?php print $right_top ?>
				</li>
				<li>
					<?php print $right ?>					
				</li>
			</ul>
		</div>
		<!-- end #sidebar -->
		<div style="clear: both;">&nbsp;</div>
	</div>
	<!-- end #page -->
</div>
<div id="footer-content">
	<div class="column1">
		<?php print $bottom1 ?>
	</div>
	<div class="column2">
		<?php print $bottom2 ?>
	</div>
</div>
<div id="footer">
	<p><?php print $footer_message ?></p>
</div>
<?php print $closure ?>
</body>
</html>
