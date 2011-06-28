<div class="node_<?php print $node->nid ?> <?php print $node->viewpage?>">
			<div class="breed_box">
			    
			    <h3 class="breed_box_title">
				<?php print l($node->title, 'node/' . $nid) ?>
				    is a <?php print $node->content['breed']['#value'] ?> and has tilted his head <?php print $node->content['tilt_total']['#value'] ?> times!
			    </h3>
			    <div class="breed_box_action">
			    <?php print $node->content['share_facebook']['#value'] ?>
			    <?php print $node->content['share_twitter']['#value'] ?>
			    </div>
			    <div class="clearfix"></div>

			    
			    <div class="breed_box_thumbs">
			    <?php $iimage = 0; ?>
			    <?php // $node->field_image = array_reverse($node->field_image); ?>
			    <?php foreach ($node->field_image as $image) { ?>
			      <?php print l(theme('imagecache', 'browse_frequent',$image['filepath']), 'node/'. $image['data']['tilt_nid'], array('html' => TRUE)); ?>
			      <?php $iimage++; ?>
			      <?php if ($iimage > 11) break; ?>
			    <?php } ?>								
				<div class="clearfix"></div>
			    </div>
			    
			    <a href="<?php print url('node/'. $node->nid) ?>" class="view_all_breed">
				View All <?php print $node->content['tilt_total']['#value'] ?> Head tilt's
			    </a>

			    
			</div><!--.breed_box-->
</div>			