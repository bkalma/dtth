<div class="node_<?php print $node->nid ?> <?php print $node->viewpage?>">
<div class="post_box node_<?php print $node->nid?>">			      
  <div class="post_box_content">			          
    <aside class="pic small">				              
      <?php print $node->rate_thumbsup['#value'] ?>      				             				              
      <div class="img_wrapper">        
        <?php print l(theme('imagecache', 'browse_recent',$node->field_image[0]['filepath']), 'node/'. $node->nid, array('html' => TRUE)); ?>                             
      </div>				              
      <div class="pic_actions">		    
        <div class="info_time"><?php print format_interval(time() - $node->created); ?></div>     
<?php
          $links = $node->links;
          $flag = $links['flag-flagthis']; 
                ?>	                                      				             
        <?php print $flag['title']; ?>                                         				              
        <div class="info_share"><?php print $node->content['share_facebook']['#value']; ?><?php print $node->content['share_twitter']['#value'];	?></div>
      </div>			              
    </aside>			              			    
    <div class="detail">				
      <h3 class="quote"><?php print $node->content['comment_topvote']['#value'] ?></h3>
      <?php if ($node->content['comment_total']['#value'] > 0) { ?>
      <?php print l(t('View all !total Captions', array('!total' => $node->content['comment_total']['#value'])), 'node/'.$node->nid.'/caption', array('title' => t('View all captions'), 'attributes' => array('class' => 'view_caption ctools-use-ajax'))); ?>
      <?php } ?>				 				      				 				
      <div class="pic_thumbs">				    
        <div class="pic_thumbs_entry thumbs">					
          <div class="info">					    
            <?php print l($node->dog->title, 'node/'. $node->dog->nid) ?> is a 
            <?php print $node->content['breed']['#value'] ?> (<?php print $node->content['breed_count']['#value'] ?>) 					
          </div>
          <?php $iimage = 0; ?>				
          <?php $node->field_other_image = array_reverse($node->field_other_image); ?>	 					
          <?php foreach ($node->field_other_image as $image) { ?>                                                 
			      <?php print l(theme('imagecache', 'browse_recent_thumb',$image['filepath']), 'node/'. $image['data']['tilt_nid'], array('attributes' => array('class' => 'thumb'), 'html' => TRUE)); ?>            			      			      			      
			      <?php $iimage++; ?>
			      <?php if ($iimage > 4) break; ?>
			    <?php } ?>          
        <!--pic_thumbs_entry-->				
        </div>
      </div>
      <!--pic_thumbs-->
      <?php
        $element['#title'] = t('Add Captions');
        $element['#value'] = '<div>test</div>';    
        $element['#collapsible'] = TRUE;
        $element['#collapsed'] = TRUE;
        $element['#attributes'] = array('class' => 'add_caption_wrapper');
        //print theme('fieldset', $element); 
      
      ?>
      <?php print l(t('Add Caption') .'<span>&nbsp;</span>', 'node/'.$node->nid.'/caption', array('title' => t('Display caption'), 'html' => TRUE, 'attributes' => array('class' => 'add_caption ctools-use-ajax'))); ?>            				 				              				 				
      <div class="clearfix">      
      </div>				 		
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