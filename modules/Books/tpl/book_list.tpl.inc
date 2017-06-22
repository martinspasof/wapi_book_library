<div class="container">
    <h2>Book List</h2>
    
    <table id="book_list_table" class="table">
        <thead>
            <tr>
                <th>&nbsp;</th>
                <th>Book Title</th>
                <th>Author</th>
                <th>ISBN</th>
                <th>Publish Date</th>
                <th style="width: 80px;">Resume</th>
            </tr>
        </thead>
        
        <tbody>
            <?php
            foreach ($this->get('get_books') as $key => $data) {
             
                 $book_title = trim(strtolower($data['book_title']));
                 $book_title = str_replace(' ', '_', $book_title);
                 $path = ROOT . '/media/cover/uploads/'.$book_title;
                 $web_root = WEB_ROOT . '/media/cover/uploads/'.$book_title;
                 $files = scandir($path);
              ?>
              <tr id="<?= 'book_' . $data['book_id']; ?>">
                  <td>
                      <img src="<?= $web_root.'/'.$files[2] ?>" alt="<?php echo $book_title; ?>" style="width:150px;height:128px;">
                  </td>
                  <td><?= $data['book_title']; ?></td>
                  <td><?= $data['author']; ?></td>
                  <td><?= $data['isbn']; ?></td>
                  <td><?= $data['publish_date']; ?></td>
                  <td><?= $data['resume']; ?></td>
              </tr>
    <?php } ?>
        </tbody>
    </table>
</div>
<script>
  $(document).ready(function () {

      // DataTable
      var table = $('#book_list_table').DataTable({"bPaginate": false}, {"bSortable": false});

 
  });
</script>