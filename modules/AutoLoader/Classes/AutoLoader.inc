<?php

class AutoLoader {

  static public function loader($className) {
    $filename = ROOT."/modules/".$className."/Classes/" . str_replace("\\", '/', $className) . ".inc";
    if (file_exists($filename)) {
      include($filename);
      if (class_exists($className)) {
        return TRUE;
      }
    }
    return FALSE;
  }
}

spl_autoload_register('AutoLoader::loader');