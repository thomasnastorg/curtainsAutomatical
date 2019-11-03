<?php
require_once '/var/www/html/header.php';

?>

<link href="http://192.168.1.107/css/app.css" rel="stylesheet" >

<h4>TP-Link Smartplug Settings</h4>


<script src="http://192.168.1.107/tp-link/smart_plug.js"></script>


	<div>
      <fieldset>
<div class="controls"><label class="control-label">{{ _('IP') }}</label><input type="text" class="input-block-level" data-bind="value: ip" /></div>
          <p>
              <label>Votre message :</label>
              <textarea name="message"></textarea>
          <p>
          <p>
            <button class="btn btn-primary" data-bind="click: function() { saveData(undefined, $root.hide) }, enable: !exchanging(), css: {disabled: exchanging()}"><i class="fa fa-spinner fa-spin" data-bind="visible: sending" style="display: none;"></i> Save</button>
          </p>
      </fieldset>
	</div>
