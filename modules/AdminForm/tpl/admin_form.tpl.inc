
<div class="container" style="margin-left: 40px;">
    <img src="<?= WEB_ROOT . '/modules/images/wapi_logo.png' ?>" alt="wapi_logo" style="width:292px;height:68px;margin-bottom: 10px;margin-left: -10px;">
    <div class="row">
        <form  method="post" id="admin-form" enctype="multipart/form-data" accept-charset="UTF-8" role="form">
            <div class="form-group col-xs-10 col-sm-4 col-md-4 col-lg-4">
                <label for="Book Title">Book Title</label>
                <input type="text" class="form-control" id="book_title" name="book_title" placeholder="Book Title">
            </div>
            <div class="form-group col-xs-10 col-sm-4 col-md-4 col-lg-4">
                <label for="publish_date">Publish Date</label>
                <div class="input-group date" id="publish_date">
                    <input type="text" class="form-control" name="publish_date" placeholder="Publish Date" />
                    <span class="input-group-addon"><span class="glyphicon-calendar glyphicon"></span></span>
                </div>
            </div>
            <div class="clearfix"></div>
            <div class="form-group col-xs-10 col-sm-4 col-md-4 col-lg-4">
                <label for="author">Author</label>
                <input type="text" class="form-control" id="author" name="author" placeholder="Author">
            </div>
            <div class="form-group col-xs-10 col-sm-4 col-md-4 col-lg-4">
                <label for="format_size">Format Size</label>
                <select id="format_size" name="format_size" class="form-control">
                    <option value="">Select Format</option>
                    <?php foreach ($this->get('format_size') as $key=>$format_size){ ?>
                    <option value="<?php echo $format_size ?>"><?php echo $format_size; ?></option>
                    <?php }?>
                </select>                
            </div>     
            <div class="clearfix"></div>
            <div class="form-group col-xs-10 col-sm-4 col-md-4 col-lg-4">
                <label for="page_count">Page Count</label>
                <input type="text" class="form-control" id="page_count" name="page_count" placeholder="Page Count">
            </div>
            <div class="col-xs-10 col-sm-10 col-md-4 col-lg-4" >
                <label for="resume">Resume</label>   
                <textarea id="resume" name="resume" class="form-control custom-control" rows="5" cols="10" style="resize:none;width:293px;height:114px;" placeholder="Resume"></textarea>
            </div>        
            <div class="clearfix"></div>
            <div style="margin-top: -60px;" class="form-group col-xs-10 col-sm-4 col-md-4 col-lg-4">
                <label for="isbn">ISBN</label>
                <input type="text" class="form-control" id="isbn" name="isbn" placeholder="ISBN">
            </div> 
            <div class="clearfix"></div>
            <div class="form-group col-xs-10 col-sm-10 col-md-4 col-lg-4">
                <label for="input_file">File input</label>
                <img src="<?= WEB_ROOT . '/modules/images/image_icon.png' ?>" alt="image_icon" style="width:50px;height:41px;">
                <input type="file" id="input_file" name="input_file">            
            </div>
            <div class="clearfix"></div>
            <div style="float:right;margin-right:100px;margin-top: -40px;" class="col-xs-10 col-sm-4 col-md-4 col-lg-4">
                <button type="submit" class="btn btn-default" >Submit</button>
                <input type="hidden" id="user_id" name="user_id" value="<?php echo isset($_SESSION['user_id'])? $_SESSION['user_id'] : '';?>" />  
            </div>
        </form>
        <div class="clearfix"></div>

        <br /><br />
    </div>
</div>

<script type="text/javascript">
  $('#publish_date').datetimepicker({
      sideBySide: true,
      icons: {
          up: "fa fa-chevron-circle-up",
          down: "fa fa-chevron-circle-down",
          next: 'fa fa-chevron-circle-right',
          previous: 'fa fa-chevron-circle-left'
      },
      format: 'YYYY/MM/DD',
  });
  
  $(document).ready( function() {
    $(':file').on('fileselect', function(event, numFiles, label) {
        console.log(numFiles);
        console.log(label);
    });
});
  
  $(document).ready(function () {
      $('#admin-form').bootstrapValidator({
          // To use feedback icons, ensure that you use Bootstrap v3.1.0 or later
          feedbackIcons: {
              valid: 'glyphicon glyphicon-ok',
              invalid: 'glyphicon glyphicon-remove',
              validating: 'glyphicon glyphicon-refresh'
          },
          fields: {
              book_title: {
                  validators: {
                      stringLength: {
                          min: 2,
                      },
                      notEmpty: {
                          message: 'Please supply book_title'
                      }
                  }
              },
              publish_date: {
                  validators: {
                      stringLength: {
                          min: 2,
                      },
                      notEmpty: {
                          message: 'Please supply publish_date'
                      }
                  }
              },
              author: {
                  validators: {
                      notEmpty: {
                          message: 'Please supply the author'
                      }
                  }
              },
              format_size: {
                  validators: {
                      notEmpty: {
                          message: 'Please choose format size'
                      }
                  }
              },
              page_count: {
                  validators: {
                      notEmpty: {
                          message: 'Please supply page_count'
                      }
                  }
              },
              resume: {
                  validators: {
                      notEmpty: {
                          message: 'Please supply resume'
                      }
                  }
              },
              isbn: {
                  validators: {
                      notEmpty: {
                          message: 'Please supply ISBN'
                      }
                  }
              },
              input_file: {
                  validators: {
                      notEmpty: {
                          message: 'Please choose image file'
                      }
                  }
              }


          }
      })
      .on('success.form.bv', function (e) {
        alert(e);
          $('#success_message').slideDown({opacity: "show"}, "slow") // Do something ...
          $('#admin-form').data('bootstrapValidator').resetForm();

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
