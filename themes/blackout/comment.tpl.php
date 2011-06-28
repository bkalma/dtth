<?php // $Id: comment.tpl.php,v 1.1 2009/05/15 07:28:05 agileware Exp $ ?>
<div class="comment<?php echo ($comment->new) ? ' comment-new' : ''; echo ($comment->status == COMMENT_NOT_PUBLISHED) ? ' comment-unpublished' : ''; ?> clear-block">
  <?php echo $picture ?>
  <?php if ($comment->new): ?>
    <span class="new"><?php echo $new ?></span>
  <?php endif; ?>
  <h3 class="commentTitle"><?php echo $title ?></h3>
  <div class="metadata">
    <div class="chronodata">
      <?php echo $submitted ?>
    </div>
  </div>
  <div class="content">
    <?php echo $content ?>
  </div>
  <div class="metadata">
    <?php if ($links): ?>
      <div class="links">
        <?php echo $links; ?>
      </div>
    <?php endif; ?>
  </div>
</div>
