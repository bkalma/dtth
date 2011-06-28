<?php // $Id: block.tpl.php,v 1.1 2009/05/15 07:28:05 agileware Exp $ ?>
<div id="block-<?php echo $block->module . '-' . $block->delta; ?>" class="block block-<?php echo $block->module ?>">
  <?php if ($block->subject): ?>
    <h2 class="title"><?php echo $block->subject ?></h2>
  <?php endif;?>
  <div class="content">
    <?php echo $block->content ?>
  </div>
</div>
