<div class="node node_<?php print $node->nid ?> node_<?php print $node->type?> <?php print $node->viewpage?>">
			<div class="breed_box">
			    
			    <h3 class="breed_box_title">
				<?php print l($node->title, 'node/' . $nid) ?>
				    is a <?php print $node->content['breed']['#value'] ?> and has tilted his head <?php print $node->content['tilt_total']['#value'] ?> times!
			    </h3>			    
			    <div class="clearfix"></div>

			    
			    <div class="breed_box_thumbs">
			    <?php $i = 0; ?>
			    <?php foreach ($node->field_image as $image) { ?>
			    <?php if ($i == 0) { ?>
            <div class="row">
          <?php } ?>			    
			      <?php print l(theme('imagecache', 'browse_breed_detail',$image['filepath']), 'node/'. $image['data']['tilt_nid'], array('html' => TRUE)); ?>
			    <?php $i++; if ($i == 3) { ?>
              </div>
              <?php $i = 0; ?>
          <?php } ?>
			    <?php } ?>
			    
          <?php if ($i != 0) { ?>
            </div>
          <?php }  ?>								
				<div class="clearfix"></div>
			    </div>
			    
			    <a href="<?php print url('node/'. $node->nid) ?>" class="view_all_breed">			    
				View All <?php print $node->content['tilt_total']['#value'] ?> Head tilt's
			    </a>

			    
			</div><!--.breed_box-->
</div>			