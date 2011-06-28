<div class="node node_<?php print $node->nid ?> node_<?php print $node->type?> <?php print $node->viewpage?>">
<div class="pre_post_box">		     			      
  <div class="pre_post_box_entry has_action">  
    <?php print l($node->dog->title, 'node/'. $node->dog->nid); ?> is a			                             
    <?php print $node->content['breed']['#value'] ?> tilted his head on <?php print format_date($node->created,'custom', 'M d, Y'); ?> 			      
  </div>
  <div class="pre_post_box_action">			              
    <?php print $node->content['share_facebook']['#value']; ?>
    <?php print $node->content['share_twitter']['#value'];	?>			      
  </div>
  <div class="clearfix"> </div>			      
</div>
<div class="post_box">			   
  <div class="post_box_content">			     
    <aside class="pic big">				       
      <?php print $node->rate_thumbsup['#value'] ?>      				             				       
      <div class="img_wrapper">
        <a href="<?php print $node_url ?>">
        <?php print_r($node->field_image[0]['view']) ?>
        </a>                      
      </div>				       
      <div class="pic_actions">		
        <?php
          $links = $node->links;
          $flag = $links['flag-flagthis']; 
        ?>	                             				    
        <div class="info_time"><?php print format_interval(time() - $node->created); ?> - </div>
        <?php print $flag['title']; ?> 
        <!---<div class="info_share"><?php print $node->content['share_facebook']['#value']; ?>
        <?php print $node->content['share_twitter']['#value'];	?></div>--->				       
      </div>			         
    </aside>			         
    <div class="detail detail_big ">				     				       
      <div class="wuote_wide_wrapper">				             
        <h3 class="quote_wide"><?php print $node->content['comment_topvote']['#value'] ?></h3>				       
      </div>
<?php if ($page == 0) { ?>
  <?php /* <a href="<?php print $node_url?>" class="view_caption"> View all <?php print $node->content['comment_total']['#value'] ?> Captions <span>&nbsp;</span></a> */ ?>
  <?php print  $node->content['comment_links']['#value'] ?>
<?php } else { ?>
  <?php /*<div class="caption_box">
    <?php print $node->content['comment_form']['#value'] ?>
  </div>
  <div class="captions">
    <?php print $node->content['comment']['#value'] ?>
  </div>
  */ ?>
  <?php print  $node->content['comment_links']['#value'] ?>    
  
<?php } ?>
      
      <div class="clearfix"></div>
      <a name="captions"></a>	  
      <div class="view_caption_ajax" style="display: none"></div>				     			    
    </div>
    <!--.detail-->				 			    
    <div class="clearfix">
    </div>				 			
  </div>
  <!--.post_box_content-->		    
</div>
<!--.post_box-->
</div>