<?php
  // For CLI, current working directory is the one you call your command at, 
  // not the one your script is located in.
  set_include_path(get_include_path() . PATH_SEPARATOR . dirname(__DIR__));

  require_once 'form_validation.inc';

  do
  {
    $line = trim(fgets(STDIN));
    if (!empty($line))
      print("..." . (preg_match(PHONE_NUMBER_REGEX, $line) ? "yes" : "no") . "\n");
  } while (!empty($line));
?>
