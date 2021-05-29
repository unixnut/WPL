<?php
/** @file
  @copyright (C) 2013 Alastair Irvine <alastair@plug.org.au>
  @license This project is released under the GNU General Public License
 
  Licence:
      This program is free software; you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation; either version 2 of the License, or (at
      your option) any later version.
 
      See http://www.gnu.org/licenses/gpl-2.0.html for more information.
 
      You can find the complete text of the GPLv2 in the file
      /usr/share/common-licenses/GPL-2 on Debian systems.
*/

  require_once 'HTML/QuickForm2/Rule.php';

  require_once 'recaptchalib.php';


  /**
   * A rule that can be attached to a form (not an element!) that 
   * ensures the user entered the correct reCAPTCHA code.
   *
   * @note Even though the rule object is attached to the form, it is 
   * indirectly associated with a given element.  (Since the form itself 
   * validates by checking for validity of all the elements, then 
   * checking for any errors that have been added to elements by rules.)
   */
  class ReCaptchaFormRule extends HTML_QuickForm2_Rule
  {
    private $privatekey;
    private $element_id;

    private $recaptcha_error_code = null;

    private $warning_msg;


    /**
     * ReCaptchaFormRule Constructor
     *
     * @param $form     the HTML_QuickForm2 object
     * @param $element_id   the ID attribute of the associated QuickForm2 element
     * @param $privatekey   the reCAPTCHA private key used by the API
     * @param $warning_msg  (optional) The message to show if validation failed because the reCAPTCHA was incorrect
     */
    function __construct($form, $element_id, $privatekey, $warning_msg = null)
    {
      parent::__construct($form);

      $this->element_id = $element_id;
      $this->privatekey = $privatekey;

      $this->warning_msg = is_null($warning_msg) ? "reCAPTCHA code was incorrect or not provided" : $warning_msg;
    }


    protected function validateOwner()
    {
      $resp = recaptcha_check_answer($this->privatekey,
                              $_SERVER["REMOTE_ADDR"],
                              $_POST["recaptcha_challenge_field"],
                              $_POST["recaptcha_response_field"]);

      // save the error for use when re-displaying the reCAPTCHA
      $this->recaptcha_error_code = $resp->error;

      // tell HTML_QuickForm2 whether the rule passed
      return $resp->is_valid;
    }


    /**
     * Triggers a form validation failure by adding an error to the
     * static element that contains the reCAPTCHA.
     */
    protected function setOwnerError()
    {
      $this->owner->getElementById($this->element_id)->setError($this->warning_msg);
    }


    /**
     * Provides the code returned by the API.  Used by ReCaptchaManager.
     */
    public function get_error_code()
    {
      return $this->recaptcha_error_code;
    }
  }
?>
