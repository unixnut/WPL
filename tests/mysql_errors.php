#!/usr/bin/php
<?php
    require_once dirname(__DIR__) . '/vendor/autoload.php';

    $s = "SQLSTATE[HY000] [2005] Unknown MySQL (ha ha) server host 'asfdasdf978asd78asd78g78asdf9.xyz' (25)";
    $code = \WPL\MySQL\Helper::decode_msg($s);

    printf("Code = %d\n", $code);
?>
