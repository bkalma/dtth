<?php
// $Id: block.tpl.php,v 1.1 2008/08/12 20:32:34 doncoryon Exp $
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block->module ?> unstyled-block">
	<?php if ($block->subject): ?> <h3><?php print $block->subject ?></h3> <?php endif;?>
	<div class="content"><?php print $block->content ?></div>
</div>
