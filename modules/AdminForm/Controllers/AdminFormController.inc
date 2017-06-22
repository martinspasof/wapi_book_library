<?php

  $format_size = array("A0","A1","A2","A3","A4","A5","A6","A7","A8");  
  $admin_form = new BaseModuleTemplater(ROOT . '/modules/AdminForm/tpl/admin_form.tpl.inc');
  $admin_form->set('format_size',$format_size);
  $admin_form->publish();

