<?php

define('ROOT', dirname($_SERVER['SCRIPT_FILENAME']));
$WEB_ROOT = "http://" . $_SERVER['HTTP_HOST'] . dirname($_SERVER['PHP_SELF']) . "/";
define('WEB_ROOT', $WEB_ROOT);
define('SITE_ROOT', realpath(dirname(__FILE__)));

include ROOT . '/html/header.inc';
require_once("modules/AutoLoader/Classes/AutoLoader.inc");
require './Db.inc';

//load login form if user is not authentication
if (!isset($_SESSION['username'])) {
  include ROOT . '\modules\LoginForm\Controllers\LoginController.inc';
}
else {
  new Books('insert_books');
  new Books('upload_cover_book_image');
  include ROOT . '\modules\Menu\Controllers\MenuController.inc';
  if (isset($_GET['menu_id'])) {
    switch ($_GET['menu_id']) {
      case 1:
      default:
        include ROOT . '\modules\Books\Controllers\BooksController.inc';
        break;
      case 2:
        include ROOT . '\modules\AdminForm\Controllers\AdminFormController.inc';
        break;
    }
  }
  else {
    include ROOT . '\modules\Books\Controllers\BooksController.inc';
  }

  //logout
  if (isset($_POST['session'])) {
    switch ($_POST['session']) {
      case "destroy":
        session_destroy();
        header('Location: index.php');
        die;
        break;
      default:
        break;
    }
  }
}

include ROOT . '/html/footer.inc';
