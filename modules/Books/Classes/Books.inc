<?php

class Books {

  function __construct($value = null) {

    switch ($value) {
      case 'insert_books':
        $this->insertBook();
        break;
      case 'upload_cover_book_image':
        $this->uploadBookImage();
        break;
      default:
        break;
    }
  }

  public function uploadBookImage() {
    $book_title = isset($_POST['book_title']) && $_POST['book_title'] ? $_POST['book_title'] : '';
    if ($book_title) {
      $book_title = trim(strtolower($book_title));
      $book_title = str_replace(' ', '_', $book_title);
      $uploaddir = SITE_ROOT . DIRECTORY_SEPARATOR.'media'.DIRECTORY_SEPARATOR.'cover'.DIRECTORY_SEPARATOR.'uploads' . DIRECTORY_SEPARATOR. $book_title . DIRECTORY_SEPARATOR;
    
    
      if (!file_exists($uploaddir)) {
        mkdir($uploaddir, 0777, true);
      }
      $uploadfile = $uploaddir . DIRECTORY_SEPARATOR. basename($_FILES['input_file']['name']);
      
      echo "<p>";

      if (move_uploaded_file($_FILES['input_file']['tmp_name'], $uploadfile)) {
        //echo "File is valid, and was successfully uploaded.\n";
      }
      else {
        echo "Upload failed";
      }
      echo "</p>";
    
    }
  }

  public function insertBook() {
    //$arr = isset($_POST['arr']) && $_POST['arr'] ? $_POST['arr'] : '';
    $user_id = isset($_POST['user_id']) && $_POST['user_id'] ? $_POST['user_id'] : '';
    $book_title = isset($_POST['book_title']) && $_POST['book_title'] ? $_POST['book_title'] : '';
    $publish_date = isset($_POST['publish_date']) && $_POST['publish_date'] ? $_POST['publish_date'] : '';
    $author = isset($_POST['author']) && $_POST['author'] ? $_POST['author'] : '';
    $format_size = isset($_POST['format_size']) && $_POST['format_size'] ? $_POST['format_size'] : '';
    $page_count = isset($_POST['page_count']) && $_POST['page_count'] ? $_POST['page_count'] : '';
    $resume = isset($_POST['resume']) && $_POST['resume'] ? $_POST['resume'] : '';
    $isbn = isset($_POST['isbn']) && $_POST['isbn'] ? $_POST['isbn'] : '';
    
    
    $db = new Db();
    $escape_resume = $db->escape($resume);
    $fields = array();   
    $fields['book_title'] =$book_title;
    $fields['publish_date'] =$publish_date;
    $fields['author'] =$author;
    $fields['book_format'] =$format_size;
    $fields['page_count'] =$page_count;
    $fields['resume'] =$escape_resume;
    $fields['isbn'] =$isbn;

    
    
    if($user_id){     
      //create record in books
      $table = 'books';
      $insert_book_data = $db->insert($table, $fields);
      $sql_max_book_id = "SELECT MAX(book_id) as last_book_id FROM `books`;";
      //get book_id from last record in table `books`
      $get_max_book_id = $db->select($sql_max_book_id);
      $book_id = $get_max_book_id[0]['last_book_id'];
      
      //create records about connection between user_id and book_id
      if(isset($book_id) && $book_id){       
          $table = 'users_books';
          $fields = array();
          $fields['user_id'] =$user_id;
          $fields['book_id'] =$book_id;
          $insert_book_data = $db->insert($table, $fields);
      }
      
    }

 
  }

  public function getBooks($id = null, $get_val = null) {


    $sql_get_data = "SELECT * 
                          FROM books as bk
                        LEFT JOIN users_books u_bk 
                        ON bk.book_id = u_bk.book_id
                        ORDER BY bk.book_id";


    $db = new Db();
    $get_data = $db->select($sql_get_data);


    return $get_data;
  }

}
