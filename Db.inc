<?php

class Db {

    // The database connection
    protected static $connection;  
    protected static $result;

    /**
     * Connect to the database
     * 
     * @return bool false on failure / mysqli MySQLi object instance on success
     */
    public function connect() {
        // Try and connect to the database
        if (!isset(self::$connection)) {
            // Load configuration as an array. Use the actual location of your configuration file
            $config = parse_ini_file('./configuration/config.ini');
            self::$connection = new mysqli($config['servername'], $config['username'], $config['password'], $config['dbname']);
        }

        // If connection was not successful, handle the error
        if (self::$connection === false) {
            // Handle error - notify administrator, log to a file, show an error screen, etc.
            return false;
        }
        return self::$connection;
    }

    /**
     * Query the database
     *
     * @param $query The query string
     * @return mixed The result of the mysqli::query() function
     */
    public function query($query) {
        // Connect to the database
        $connection = $this->connect();

        // Query the database
        $result = $connection->query($query);

        return $result;
    }

    /**
     * Fetch rows from the database (SELECT query)
     *
     * @param $query The query string
     * @return bool False on failure / array Database rows on success
     */
    public function select($query) {
        $rows = array();
        $result = $this->query($query);
        if ($result === false) {
            return false;
        }
        while ($row = $result->fetch_assoc()) {
            $rows[] = $row;
        }
        return $rows;
    }
    
    
     /**
     * Helper function for process_where
     *
     * @param $array
     * @return string
     */
    private function join_array($array){
        $nr = 0;
        $query = '';
        foreach ($array as $key => $value) {
            if (is_object($value) || is_array($value) || is_bool($value)) {
                $value = serialize($value);
            }
            $query .= " '" . $this->escape($value) . "'";
            $nr++;
            if ($nr != count($array)) {
                $query .= ',';
            }
        }
        return trim($query);
    }
    
    /* Insert function */
    /**
     * Insert a row in a table
     *
     * @param $table
     * @param array $fields
     * @param bool|false $appendix
     * @param bool|false $ret
     * @return bool|Database
     * @throws Exception
     */
    public function insert($table, $fields = array(), $appendix = false, $ret = false){
        $this->result = null;
        $query = 'INSERT INTO';
        $query .= ' ' . $this->escape($table);
        if (is_array($fields)) {
            $query .= ' (';
            $num = 0;
            foreach ($fields as $key => $value) {
                $query .= ' `' . $key . '`';
                $num++;
                if ($num != count($fields)) {
                    $query .= ',';
                }
            }
            $query .= ' ) VALUES ( ' . $this->join_array($fields) . ' )';
        } else {
            $query .= ' ' . $fields;
        }
        if ($appendix) {
            $query .= ' ' . $appendix;
        }
        if ($ret) {
            return $query;
        }

        
        $this->result = $this->query($query); 
        if (mysqli_error($this->connect()) != '') {
            $this->error(mysqli_error($this->connect()));
            $this->result = null;
            return false;
        } else {
            return $this;
        }
    }   

    /**
     * Fetch the last error from the database
     * 
     * @return string Database error message
     */
    public function error() {
        $connection = $this->connect();
        return $connection->error;
    }

    /**
     * Quote and escape value for use in a database query
     *
     * @param string $value The value to be quoted and escaped
     * @return string The quoted and escaped string
     */
    public function escape($value) {
        $connection = $this->connect();
        return $connection->real_escape_string($value);
    }

}
