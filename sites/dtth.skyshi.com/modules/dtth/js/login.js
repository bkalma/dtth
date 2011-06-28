function dtth_facebook_upload2_onlogin_ready() {
  // http://github.com/facebook/connect-js/issues/194
  if (!FB.getSession()) {
    return;
  }
  $('#dtth-upload2-form #edit-signin-service').val('facebook');
  $('#dtth-upload2-form').append('<input type="hidden" name="op" value="Login">');
  $('#dtth-upload2-form').submit();  
}

function dtth_facebook_onlogin2_ready() {
  // http://github.com/facebook/connect-js/issues/194
  if (!FB.getSession()) {
    return;
  }
  $("#fbconnect-autoconnect-form").submit();
}

function dtth_facebook_onlogin3_ready() {
  // http://github.com/facebook/connect-js/issues/194
  if (!FB.getSession()) {
    return;
  }
  $('#dtth-upload2-form').append('<input type="hidden" name="op" value="Login">');
  $('#dtth-upload2-form').append('<input type="hidden" name="op" value="Login">');
  $('#dtth-upload2-form').submit();  
}

function dtth_facebook_signin_onlogin_ready() {
  // http://github.com/facebook/connect-js/issues/194
  if (!FB.getSession()) {
    return;
  }
  $('#dtth-signin-form #edit-signin-service').val('facebook');
  $('#dtth-signin-form').append('<input type="hidden" name="op" value="Login">');
  $('#dtth-signin-form').submit();  
}


