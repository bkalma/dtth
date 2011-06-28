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
			<?php if (isset($header)) { ?><div id="banner"><?php print $header ?></div><?php } ?>
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
					<h2>Veroeros sit dolore</h2>
					<p><strong>Donec turpis orci</strong> facilisis et ornare eget, sagittis eu massa. Quisque dui diam, euismod et lobortis sed etiam lorem ipsum dolor etiam nullam et faucibus. <a href="#">More&#8230;</a></p>
				</li>
				<li>
					<h2>Categories</h2>
					<ul>
						<li><span>09.13.09</span><a href="#">Vestibulum risus vitae</a></li>
						<li><span>09.13.09</span><a href="#">Condimentum et molestie</a></li>
						<li><span>09.13.09</span><a href="#">Facilisis sed vestibulum</a></li>
						<li><span>09.13.09</span><a href="#">Ipsum primis et sed luctus </a></li>
						<li><span>09.13.09</span><a href="#">Ultrices posuere nulla </a></li>
						<li><span>09.13.09</span><a href="#">Accumsan lorem sodales </a></li>
						<li><span>09.13.09</span><a href="#">Scelerisque consectetur </a></li>
						<li><span>09.13.09</span><a href="#">Maecenas quam aliquet</a></li>
					</ul>
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
		<h2>Volutpat quisque sed et aliquam</h2>
		<p><strong>Maecenas ut ante</strong> eu velit laoreet tempor accumsan vitae nibh. Aenean commodo, tortor eu porta convolutpat elementum. Proin fermentum molestie erat eget vehicula. Aenean eget tellus mi. Fusce scelerisque odio quis ante bibendum sollicitudin. Suspendisse potenti. Vivamus quam odio, facilisis at ultrices nec, sollicitudin ac risus. Donec ut odio ipsum, sed tincidunt. <a href="#">Learn more&#8230;</a></p>
	</div>
	<div class="column2">
		<ul class="list">
			<li><a href="#">Tempor accumsan vitae sed nibh dolore</a></li>
			<li><a href="#">Aenean commodo, tortor eu porta veroeros</a></li>
			<li><a href="#">Fermentum molestie erat eget consequat</a></li>
			<li><a href="#">Donec vestibulum interdum diam etiam</a></li>
			<li><a href="#">Vehicula aenean eget sed tellus blandit</a></li>
		</ul>
	</div>
</div>
<div id="footer">
	<p><?php print $footer_message ?></p>
</div>
<?php print $closure ?>
</body>
</html>
