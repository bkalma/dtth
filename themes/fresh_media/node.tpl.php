<?php
// $Id: node.tpl.php,v 1.1 2008/08/12 20:32:34 doncoryon Exp $
?>
  <div class="node<?php if ($sticky) { print " sticky"; } ?><?php if (!$status) { print " node-unpublished"; } ?>">
    <?php if ($picture) {
      print $picture;
    }?>
    <?php if ($page == 0) { ?><h2><a href="<?php print $node_url?>"><?php print $title?></a></h2><?php }; ?>
    <span class="submitted"><?php print $submitted?><?php print $terms?></span>
    <div class="content"><?php print $content?></div>
    <?php if ($links) { ?><div class="postmeta"><?php print $links?></div><?php }; ?>
  </div>
