<?php

class LoginForm {

  function __construct() {
    
  }

  public function getUserData($stack = array()) {
    $clause_user_id = '';
    $is_user_id = false;
    if (isset($stack['user_id']) && $stack['user_id']) {
      $is_user_id = true;
      $clause_user_id = " AND us.id='{$stack['user_id']}' ";
    }    
    
    $clause_fname = '';
    $is_fname = false;
    if (isset($stack['fname']) && $stack['fname']) {
      $is_fname = true;
      $fname = strtolower($stack['fname']);
      $clause_fname = " AND LOWER(us.fname)='{$fname}' ";
    }
    
    $clause_lname = '';
    $is_lname = false;
    if (isset($stack['lname']) && $stack['lname']) {
      $is_lname = true;
      $lname = strtolower($stack['lname']);
      $clause_lname = " AND LOWER(us.lname)='{$lname}' ";
    }
    
    $clause_password = '';
    $is_pass = false;
    if (isset($stack['pass']) && $stack['pass']) {
      $is_pass = true;
      $clause_password = " AND us.pass='{$stack['pass']}' ";
    }

    $sql_get_user_data = "SELECT us.*,us_r.* 
                            FROM users as us
                          LEFT JOIN user_roles us_r 
                          ON us.role_id = us_r.id
                          WHERE 1=1
                          $clause_user_id
                          $clause_fname
                          $clause_lname
                          $clause_password
                          ORDER BY us.user_id";

    

    $db = new Db();
    $get_user_data = $db->select($sql_get_user_data);

//    if (isset($id) && $id) {
//      echo '<user_info style="display:none">' . json_encode($get_data) . '</user_info>';
//    }

    $user_data = array();
    $user_data['is_auth'] = $is_fname && $is_lname && $is_pass;    
    $user_data['get_user_data'] = $get_user_data;
    
    return $user_data;
  }

}
