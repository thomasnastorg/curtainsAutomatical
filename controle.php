<?php require 'header.php'; ?>



<link href="css/app.css" rel="stylesheet" >


<div class="card border-primary mb-3 card-me"  style="max-width:500;">

<center>
	<legend>Prise impriment 3D</legend>
		<div class="custom-control custom-switch" style="max-width:500;">
      <input type="checkbox" class="custom-control-input" id="customSwitch1" checked="">
      <label class="custom-control-label" for="customSwitch1">OFF / ON</label>
    </div>
		<legend>Chambre T.N</legend>

	  <div class="form-group">
	    <div class="custom-control custom-switch">
	      <input type="checkbox" class="custom-control-input" id="customSwitch2" checked="">
	      <label class="custom-control-label" for="customSwitch1">OFF / ON</label>
	    </div>
		</div>
			<div class="form-group">
				<div class="custom-control custom-switch">
					<input type="checkbox" class="custom-control-input" id="customSwitch3" checked="">
					<label class="custom-control-label" for="customSwitch1">OFF / ON</label>
				</div>
			</div>
</div>
</center>


<!-- ko foreach: arrSmartplugs -->
<a class="pull-right" href=#" data-toggle="tooltip" data-html="true" data-bind="click: $root.toggleRelay, visible: $root.loginState.loggedIn(), tooltip: {title: label, placement: 'bottom'}" style="display: none;float: left;"><i class="icon" data-bind="css: [currentState(), icon(),(($root.processing().indexOf(ip()) > -1) ? 'icon-spin' : '')].join(' ')"></i></a>
<!-- /ko -->

<div id="TPLinkSmartPlugWarning" data-bind="with: selectedPlug" class="modal hide fade">
    <div class="modal-header">
        <a href="#" class="close" data-dismiss="modal" aria-hidden="true">&times;</a>
        <h3>TP-Link Smartplug</h3>
    </div>
    <div class="modal-body">
        <p>
            <!--ko text: label()--><!--/ko--> is currently <!--ko text: currentState()--><!--/ko-->.
        </p>
		<p>
            {{ _('Are you sure you want to proceed?') }}
        </p>
    </div>
    <div class="modal-footer">
        <a href="#" class="btn" data-dismiss="modal" aria-hidden="true" data-bind="click: $root.cancelClick">{{ _('Cancel') }}</a>
        <a href="#" class="btn btn-danger" data-bind="click: $root.turnOff">{{ _('Proceed') }}</a>
    </div>
