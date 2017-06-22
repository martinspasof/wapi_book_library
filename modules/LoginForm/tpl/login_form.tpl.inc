<link rel="stylesheet" type="text/css" href="<?php echo WEB_ROOT ?>/modules/LoginForm/css/login.css">

<div class="container">
    <div class="row">
        <div class="col-md-4 col-md-offset-4">
            <div class="panel panel-default">
                <div class="panel-heading">
                    <h3 class="panel-title">Please sign in</h3>
                </div>
                <div class="panel-body">
                    <form method="post" id="login-form" accept-charset="UTF-8" role="form" >
                        <fieldset>
                            <div class="form-group">
                                <input class="form-control" placeholder="First Name" name="fname" type="text">
                            </div>
                            <div class="form-group">
                                <input class="form-control" placeholder="Last Name" name="lname" type="text">
                            </div>
                            <div class="form-group">
                                <input class="form-control" placeholder="Password" name="pass" type="password" value="">
                            </div>
                            <div class="checkbox">
                                <label>
                                    <input name="remember" type="checkbox" value="Remember Me"> Remember Me
                                </label>
                            </div>
                            <input type="hidden" name="user_id" />          
                            <input class="btn btn-lg btn-success btn-block" type="submit" value="Login">              
                        </fieldset>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>


<script>
  $(document).ready(function () {
      $('#login-form').bootstrapValidator({
          // To use feedback icons, ensure that you use Bootstrap v3.1.0 or later
          feedbackIcons: {
              valid: 'glyphicon glyphicon-ok',
              invalid: 'glyphicon glyphicon-remove',
              validating: 'glyphicon glyphicon-refresh'
          },
          fields: {
              fname: {
                  validators: {
                      stringLength: {
                          min: 2,
                      },
                      notEmpty: {
                          message: 'Please supply your first name'
                      }
                  }
              },
              lname: {
                  validators: {
                      stringLength: {
                          min: 2,
                      },
                      notEmpty: {
                          message: 'Please supply your last name'
                      }
                  }
              },
              pass: {
                  validators: {
                      notEmpty: {
                          message: 'Please supply your password'
                      }
                  }
              }


          }
      })
      .on('success.form.bv', function (e) {
          $('#success_message').slideDown({opacity: "show"}, "slow") // Do something ...
          $('#login-form').data('bootstrapValidator').resetForm();

          // Prevent form submission
          e.preventDefault();

          // Get the form instance
          var $form = $(e.target);

          // Get the BootstrapValidator instance
          var bv = $form.data('bootstrapValidator');

          // Use Ajax to submit form data
          $.post($form.attr('action'), $form.serialize(), function (result) {
              console.log(result);
          }, 'json');
      });
  });


</script>