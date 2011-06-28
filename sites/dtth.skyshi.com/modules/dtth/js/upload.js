Drupal.behaviors.dtth_upload = function() {  
  $('#edit-tilt').live('change', function() {    
    $('#edit-tilt-temp').val($(this).val());
    $(this).append('<input type="hidden" name="op" value="Upload">');
    $('#dtth-upload2-form').submit();
    //$('#edit-upload.ctools-use-modal-processed').trigger('click');
    //this.form.clk = $('#edit-upload');
    //$('#dtth-upload2-form').val('op','Upload');        
    //$('#dtth-upload2-form').submit();
    //return false;
      
  });
  
  $("#autocomplete li div:contains('Add New Breed')").live('click', function() {
    //$('.newbreed').toggle(true);    
    $('#edit-breed').val('');    
    $('#edit-breed').append('<input type="hidden" name="op" value="Add New Breed Form">');
    $('#dtth-upload2-form').submit();
    //alert($(this).val());
  });
  /*  
  $('#node-form input, #node-form textarea').focus(function() {      
    $(this).attr('value','');      
  });*/
  /*$('#node-form input, #node-form textarea').focusout(function() {      
    if ($(this).val() == '') {
      $(this).val($(this).attr('default_value'));
    }
  });*/  
};
  
/*
Drupal.behaviors.modalFrameExample = function() {
  $('.modalframe-example-child:not(.modalframe-example-processed)').addClass('modalframe-example-processed').click(function() {
    var element = this;

    // This is our onSubmit callback that will be called from the child window
    // when it is requested by a call to modalframe_close_dialog() performed
    // from server-side submit handlers.
    function onSubmitCallbackExample(args, statusMessages) {
      // Display status messages generated during submit processing.
      if (statusMessages) {
        $('.modalframe-example-messages').hide().html(statusMessages).show('slow');
      }

      if (args && args.message) {
        // Provide a simple feedback alert deferred a little.
        setTimeout(function() { alert(args.message); }, 500);
      }
    }

    // Hide the messages are before opening a new dialog.
    $('.modalframe-example-messages').hide('fast');

    // Build modal frame options.
    var modalOptions = {
      url: $(element).attr('href'),
      autoFit: true,
      onSubmit: onSubmitCallbackExample
    };

    // Try to obtain the dialog size from the className of the element.
    var regExp = /^.*modalframe-example-size\[\s*([0-9]*\s*,\s*[0-9]*)\s*\].*$/;
    if (typeof element.className == 'string' && regExp.test(element.className)) {
      var size = element.className.replace(regExp, '$1').split(',');
      modalOptions.width = parseInt(size[0].replace(/ /g, ''));
      modalOptions.height = parseInt(size[1].replace(/ /g, ''));
    }

    // Open the modal frame dialog.
    Drupal.modalFrame.open(modalOptions);

    // Prevent default action of the link click event.
    return false;
  });
};*/