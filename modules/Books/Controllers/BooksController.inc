<?php

  $books = new Books(); 
  $book_list = new BaseModuleTemplater(ROOT . '/modules/Books/tpl/book_list.tpl.inc');
  $book_list->set('get_books', $books->getBooks());
  $book_list->publish();

