<?php
// $Id: page.tpl.php,v 1.1.4.1 2008/08/15 23:16:13 doncoryon Exp $
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php print $language->language ?>" xml:lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title ?></title>
  <?php print $head ?>
  <?php print $styles ?>
  <?php print $scripts ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
</head>

<body>

<!-- wrap starts here -->
<div id="wrap-out"><div id="wrap-in"><div id="wrap">

	<!--header -->
	<div id="header">			
		<?php if ($site_name) { ?><h1 id="logo-text"><a href="<?php print $front_page ?>" title="<?php print t('Home') ?>"><?php print $site_name ?></a></h1><?php } ?>		
		<p id="intro">
		<?php if ($site_slogan) { ?><?php print $site_slogan ?><?php } ?>
		</p>		
		
		<div  id="nav">
			<?php if (isset($primary_links)) { ?><?php print theme('links', $primary_links, array('class' => 'links', 'id' => 'navlist')) ?><?php } ?>	
		</div>	
				
	<!--header ends-->					
	</div>
	
	<!-- content-wrap starts -->
	<div id="content-top-wrap"></div>
	<div id="content-wrap">
				
		<div id="main">
	        <?php if ($mission) { ?><div id="mission"><?php print $mission ?></div><?php } ?>
	      
	        <?php if ($title) { ?><h1 class="node-title"><?php print $title ?></h1><?php } ?>
	        <div class="tabs"><?php print $tabs ?></div>
	        <?php if ($show_messages) { print $messages; } ?>
	        <?php print $help ?>
	        <?php print $content; ?>
	        <?php print $feed_icons; ?>				
						
		</div>
		<!-- main ends -->
		
		<!-- sidebar starts -->
		<div id="sidebar">
			<?php if ($right) { ?> <?php print $right ?> <?php } ?>				
		</div>
		<!-- sidebar ends -->
		
	
	</div>
	<div id="content-bottom-wrap"></div>
	<!-- content-wrap ends-->	
	
	<!-- footer starts here -->	
	<div id="footer-wrap"><div id="footer-content">
		<div class="col float-left space-sep">
			<?php if ($footer1) { ?> <?php print $footer1 ?> <?php } ?>
		</div>
		<div class="col float-left">
			<?php if ($footer2) { ?> <?php print $footer2 ?> <?php } ?>
		</div>		
		<div class="col2 float-right">
			<?php if ($footer3) { ?> <?php print $footer3 ?> <?php } ?>	
		</div>
	</div></div>
		<div id="footer-message">
			<?php if ($footer_message) { ?> <?php print $footer_message ?> <?php } ?>
		</div>
		<div id="footer">
		
		</div>
	<div class="clearer"></div>
	<!-- footer ends here -->

<!-- wrap ends here -->
</div></div></div>

<?php print $closure ?>

</body>
</html>
