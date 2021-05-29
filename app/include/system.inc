<?php
  /** @file
   * Functions, classes etc. for dealing with OS concepts
  */


  class ProgramException extends RuntimeException
  {
  }


  /**
   * A program couldn't be executed
   */
  class ProgramExecutionException extends ProgramException
  {
  }


  /**
   * A program returned an error
   */
  class ProgramFailureException extends ProgramException
  {
  }


?>
