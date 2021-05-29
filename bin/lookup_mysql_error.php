#! /usr/bin/php
<?php
  require_once dirname(__DIR__) . '/vendor/autoload.php';
?>
<?php
    printf("%s\n", \WPL\MySQL\Helper::desc((int)$argv[1]));


# vim: set tabstop=4 shiftwidth=4 :
# Local Variables:
# tab-width: 4
# end:
?>
