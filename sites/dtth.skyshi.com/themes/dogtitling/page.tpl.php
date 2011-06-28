<!doctype html>
<!--[if lt IE 7 ]> <html lang="en" class="no-js ie6"> <![endif]-->
<!--[if IE 7 ]>    <html lang="en" class="no-js ie7"> <![endif]-->
<!--[if IE 8 ]>    <html lang="en" class="no-js ie8"> <![endif]-->
<!--[if IE 9 ]>    <html lang="en" class="no-js ie9"> <![endif]-->
<!--[if (gt IE 9)|!(IE)]><!--> 
<html lang="en" class="no-js">    
  <!--<![endif]-->   
  <head>         
    <meta charset="UTF-8">	          
    <?php print $head ?>          
    <title>      
      <?php print $head_title ?>    
    </title>         
    <?php print $styles ?>         
    <?php print $scripts ?>	          
    <meta name="viewport" content="width=device-width, initial-scale=1.0">           
  </head>  
  <body>         
    <div id="container">	 	       
      <div id="header_container" class="wrapper">	     	             
        <header>		 		           
          <h1 id="title" class="logo">		                 
            <a href="<?php print $front_page ?>" title="" class="png_bg"></a>		</h1>		 		           
<?php /*<nav>		    
            <ul class="top_nav">
        			<!-- add class active to active menu -->
        			<li class="active"><a href="#" id="top_nav_bestof" class="png_bg" title="">Best of captions</a></li>
        			<li><a href="#" id="top_nav_fav" class="png_bg" title="">Our favorite titls</a></li>
        			<li><a href="#" id="top_nav_stat" class="png_bg" title="">Stats</a></li>
        		    </ul>            		
                    </nav>	*/ ?>	     		           
          <div id="top">
            <?php print $top ?>
          </div>          
          <div class="clearfix">
          </div>		 	             
        </header>	     	       
      </div>      
      <!--#header_container-->        	       
      <div id="main" class="wrapper">        
        <?php if (!empty($header)) { ?>	     	             
        <section id="user_action">
          <div class="sidebar_widget">		           
            <?php print $header ?>	    
          </div>         
          <div class="clearfix"></div>
        </section>	     	             
        <?php } ?>         
        <section id="content_container">                     
          <?php print $breadcrumb; ?>                     
          <?php if ($tabs) { ?>             
          <nav id="top_tab" class="tabs">              
            <?php print $tabs ?>            
          </nav>            
          <div class="clearfix">            
          </div>          
          <?php } ?>		 		                    		                		                		          		 		           
          <div id="content" class="post_boxes multiplebgs">		     		                                                                                      
            <?php if ($messages): print $messages; endif; ?>             
            <?php print $content ?>            	     		           
          </div>          
          <!--content-->		 		           
          <aside id="sidebar">		     		                		     		                 
            <?php print $right ?>	     		           
          </aside>          
          <!--#sidebar-->		 		           
          <div class="clearfix">          
          </div>		 	             
        </section>	     	       
      </div>      
      <!--#main-->	          
    </div>    
    <!--#container-->              
    <div id="footer_container" class="multiplebgs">	
      <div id="footer">	     	    
        <footer class="wrapper">		
          <div id="col_1" class="col multiplebgs">		    
            <?php print $footer_col1 ?>
          </div>		
          <div id="col_3" class="col ">
            <?php print $footer_col3 ?>		    		               		               		    		
          </div>		
          <div id="col_2" class="col ">
            <?php print $footer_col2 ?>		                		                		
          </div>		
          <div class="clearfix">
          </div>		 		
          <div class="copyrights">		    
            <?php print $footer ?>		
          </div>	    
        </footer>
      </div>			     
    </div>
    <!--#footer_container-->                    
    <!--[if lt IE 7 ]>
            <script src="js/libs/dd_belatedpng.js"></script>
            <script> DD_belatedPNG.fix('img, .png_bg');</script>
            <![endif]-->      
    <?php print $closure_js ?>    
    <?php print $closure ?>       
  </body>
</html>