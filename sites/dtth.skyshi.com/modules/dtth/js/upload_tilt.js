Drupal.behaviors.tilt_focus = function(context) {  
  function showCoords(c)
  {
    $('.tilt_image_focus_rect').val(c.x+','+c.y+','+c.w+','+c.h);  	
  };
  
  if (Drupal.settings.upload_tilt_data.width > 540 || Drupal.settings.upload_tilt_data.height > 540) {
    var allowResize = 1;
  } else {
    var allowResize = 0;
  }     
    
  $('.tilt_focus img').Jcrop({
    onChange: showCoords,
    onSelect: showCoords,
    setSelect: [ 0, 0, 540, 540],
    boxWidth: 248,
    boxHeight: 540,
    allowResize: allowResize,
    allowSelect: 0,
    aspectRatio: 540/540,
    minSize: [540, 540],
    trueSize: [Drupal.settings.upload_tilt_data.width,Drupal.settings.upload_tilt_data.height]
  });
  $('.tilt_focus img').load(function() {
    $(this).css('visibility', 'visible');
  });  
  //console.log([Drupal.settings.upload_tilt_data.width,Drupal.settings.upload_tilt_data.height]);
}