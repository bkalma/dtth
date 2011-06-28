Drupal.behaviors.dtth = function() {
  //$('input, textarea').placeholder();
  
  // handle fix for chrome on textarea placeholder
  $('textarea[placeholder]','.caption_add').each(function() {
    var input = $(this);
    var placeholder = input.attr('placeholder');    
    if (input.val() == '') {
      input.val(placeholder);
    }
    
    input.focus(function () {
      if (input.val() == input.attr('placeholder')) {
        input.val('');
      }
    });
    
    input.blur(function () {
      if (input.val() == '') {
        input.val(placeholder);
      }
    });
  });
    
  $('.post_btn', '.caption_add').click(function() {     
    var form = $(this).closest('form');
    $('textarea[placeholder]',form).each(function() {
      var input = $(this);
      var placeholder = input.attr('placeholder');    
      if (input.val() == placeholder) {
        input.val('');
      }
    });
    
    /*.each(function() {
      console.log(this);
      var input = $(this);
      var placeholder = input.attr('placeholder');    
      if (input.val() == placeholder) {
        input.val('');
      }
    });*/
  });


  // define breadcrumb
  $("#breadcrumb a[href!='']").addClass('node');
  $("#breadcrumb a[href!='']:last").attr('class','');
  $("#breadcrumb a[href!='']:last").addClass('last_node');
  
  // define tooltip for all a with title
  // http://flowplayer.org/tools/tooltip/index.html
  //$("a[title]").tooltip();
  
  $(document).bind('eventAfterRate', function(obj, data) {
    window.setTimeout(function() {
      var id = $(data).attr('id');
      var elm = $('#' + id + ' a.rate-button');
      if (elm.hasClass('fav')) {
        elm.parent().next().find('a').attr('title', 'Thank you for Voting!').tooltip({api: true}).show();
      }
      if (elm.hasClass('like')) {
        elm.attr('title', 'Thank you for Voting!').tooltip({api: true}).show();
      }                        
      // api must be set to true, http://flowplayer.org/tools/forum/30/37281
      //$(document).find('#' + id + ' a.rate-button').tooltip({api: true}).show();      
    }, 50);            
  });
  //rate-button like rate-thumbs-up-btn-up
}
