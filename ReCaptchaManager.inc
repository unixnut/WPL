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

  // == PEAR include files ==
  require_once 'HTML/QuickForm2.php';

  // == Other 3rd-party include files ==
  require_once 'recaptchalib.php';

  // == package include files ==
  require_once 'ReCaptchaFormRule.inc';



  /**
   * reCAPTCHA bot prevention
   * @see http://www.google.com/recaptcha
   */
  class ReCaptchaManager
  {
    const ELEMENT_ID = 'reCAPTCHA';

    protected $recaptcha = null;        //*< an HTML_QuickForm2_Element_Static object
    protected $rule = null;             //*< an HTML_QuickForm2_Rule object

    protected $recaptcha_privkey = null;
    protected $recaptcha_pubkey = null;
    protected $use_ssl;


    /**
     * Normal constructor.
     *
     * @param $use_ssl  A boolean indicating whether to tell the reCAPTCHA to fetch its resources using SSL (optional; true is default) 
     */
    function __construct($pubkey, $privkey, $use_ssl = true)
    {
      $this->recaptcha_pubkey = $pubkey;
      $this->recaptcha_privkey = $privkey;
      $this->use_ssl = $use_ssl;
    }


    /**
     * Create an HTML_QuickForm2 element and add it to the form.  Then set a 
     * rule on the form that prevents submission if the reCAPTCHA hasn't been 
     * filled in.
     *
     * The widget will actually be generated after form validation, so it has 
     * access to the recaptcha error code.
     *
     * @param $form   The form to add the rule to
     * @param $elem   (optional) The specific element to add the static to; defaults to $form
     */
    public function add_captcha(HTML_QuickForm2 $form, HTML_QuickForm2_Node $elem = null)
    {
      if (is_null($elem))
        $elem = $form;

      $this->recaptcha = $elem->addStatic(self::ELEMENT_ID, array('id' => self::ELEMENT_ID),
                                          array('content' => 'insert reCAPTCHA here'));


      $this->rule = new ReCaptchaFormRule($form, self::ELEMENT_ID, $this->recaptcha_privkey);
      $form->addRule($this->rule);
    }


    /**
     * Do anything to the reCAPTCHA element that should occur after form 
     * validation has been attempted.
     */
    public function update_captcha()
    {
      // TO-DO: throw an exception if the form hasn't been submitted

      // The reCAPTCHA might not have validated successfully, so generate it 
      // here in order that the error code is available 
      $this->recaptcha->setContent(recaptcha_get_html($this->recaptcha_pubkey,
                                                      $this->rule->get_error_code()),
                                                      $this->use_ssl);
    }
  }
?>
