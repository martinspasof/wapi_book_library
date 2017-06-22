<?php
  $menu_navigation = new BaseModuleTemplater(ROOT . '/modules/Menu/tpl/menu.tpl.inc');
  if (isset($_SESSION['role_name']) && $_SESSION['role_name']=='admin') {     
      $menu_navigation->set('book_list', 'Book List');
      $menu_navigation->set('admin', 'Admin');
      $menu_navigation->publish();
  }elseif(isset($_SESSION['role_name']) && $_SESSION['role_name']=='user'){
      $menu_navigation->set('book_list', 'Book List');     
      $menu_navigation->publish();
  }
  
