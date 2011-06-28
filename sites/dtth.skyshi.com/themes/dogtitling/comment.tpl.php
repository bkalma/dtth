<?php
// $Id: comment.tpl.php,v 1.7 2008/01/04 19:24:23 goba Exp $
?>
<div class="caption caption_<?php print $comment->cid ?>">
  <span class="caption_action">        
    <?php print $comment->links_element['rate_thumbsup']['title']; ?>
    <?php print $comment->links_element['facebook']['title']; ?>
    <?php print $comment->links_element['twitter']['title']; ?>    
  </span>
  <span class="author_img">  
<?php if ($picture) {
    print $picture;
      } ?>
  </span>
  <h4 class="author_name">
    <?php print theme('username', $comment); ?></h4>
  <span class="caption_text"> 
    <?php print $content; ?>    
    <div class="caption_date"><?php print t('@time ago',array('@time' => format_interval(time() - $comment->timestamp))); ?></div>  
  </span>  
</div>