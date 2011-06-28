<!---<div class="pre_post_box">		     			      
  <div class="pre_post_box_entry">
    <?php print l($node->title, 'node/'. $node->nid); ?> is a			                             
    <?php print $node->content['breed']['#value'] ?> and he tilted his head <?php print $node->content['tilt_total']['#value'] ?> times 			      
  </div>			      
  <div class="pre_post_box_action">			              
    <?php print $node->content['share_facebook']['#value']; ?>
    <?php print $node->content['share_twitter']['#value'];	?>			      
  </div>			 			      
  <div class="clearfix">     
  </div>		    
</div>--->
<?php
  print $node->content['tilt_display']['#value'];
?>