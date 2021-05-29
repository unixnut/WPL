<?php
  /*
  */

  // == PEAR include files ==
  
  // == Other 3rd-party include files ==
  require_once 'system.inc';  // for various exceptions

  // == global include files ==

  // == local include files ==


  // *** Definitions ***


  // *** Exported functions/classes ***
  /**
   * Uses the gpg program to encrypt using the current users's private key.
   * The receipients' keys must be trusted.
   *
   * @param     $recipients     An array of strings, each containing an e-mail address or key ID
   * @param     $plaintext      The data to encrypt
   * @return    GPG output
   * @exception ProgramExecutionException
   * @exception ProgramFailureException
   */
  function gpg_encrypt(array $recipients, $plaintext)
  {
    $cmd = "gpg --encrypt --armor";
    foreach ($recipients as $recipient)
      $cmd .= " --recipient=$recipient";

    // Note that the direction of each pipe is from the perspective of gpg
    $descriptorspec = array(
         0 => array("pipe", "r"),  // stdin is a pipe that the child will read from
         1 => array("pipe", "w"),  // stdout is a pipe that the child will write to
         2 => array("pipe", "w")); // stderr is a pipe that the child will write to

    $pipes = array();

    if (($proc_handle = proc_open($cmd, $descriptorspec, $pipes)))
    {
      fwrite($pipes[0], $plaintext);
      fclose($pipes[0]); # stdin
      $output_data = stream_get_contents($pipes[1]);
      fclose($pipes[1]); # stdout
      $error_data =  stream_get_contents($pipes[2]);
      fclose($pipes[2]); # stderr

      $exit_code = proc_close($proc_handle);
      if ($exit_code != 0)
        throw new ProgramFailureException($error_data, $exit_code);

      return $output_data;
    }
    else
      throw new ProgramExecutionException('Failed to open the process using proc_open');
  }


  // *** Local functions and classes ***
?>
