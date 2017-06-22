<?php
$class_active_menu_id_1 = 'class="active"';
$class_active_menu_id_2 = '';
$menu_name_1 = $this->get('book_list') ? $this->get('book_list') : '';
$menu_name_2 = $_SESSION['role_name']=='admin' ? $this->get('admin') : '';
if(isset($_GET['menu_id'])){
  $class_active_menu_id_1 = ($_GET['menu_id'] == 1) ? 'class="active"' : '';
  $class_active_menu_id_2 = ($_GET['menu_id'] == 2) ? 'class="active"' : '';
}
?>
<ul id="menu_nav" style="margin: 5px; margin-bottom:30px;margin-left: 40px;" class="nav nav-pills">
  <li id="menu_id_1" role="presentation" <?php echo $class_active_menu_id_1; ?>>
      <a href="?menu=book_list&menu_id=1"><?php echo $menu_name_1 ?></a>
  </li>
  <li id="menu_id_2" role="presentation" <?php echo $class_active_menu_id_2; ?>>
      <a href="?menu=admin&menu_id=2"><?php echo $menu_name_2 ?></a>
  </li>
  <div style="float:right;margin-right: 20px;font-weight: bold;">
  <?php echo $_SESSION['username'].' ('.$_SESSION['role_name'].')' ?>
  </div>
  <br/>
  
  <button type="button" style="float:right;margin-right: 20px;margin-top:5px;" onclick="logout()">Logout</button>
</ul>
 
<script>
  function logout() {

    $.ajax({
        url: "index.php",
        type: "post",
        data: {session: 'destroy'},
        success: function (response) {
          location.reload();
        },
        error: function (jqXHR, textStatus, errorThrown) {
            console.log(textStatus, errorThrown);
        }


    });
}


</script>