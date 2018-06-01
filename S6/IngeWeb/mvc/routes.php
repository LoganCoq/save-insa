<?php
    function call($cont, $act) {
        require_once('controllers/controller_'.$cont.'.php');
        switch($cont) {
            case 'pages':
                $controller = new PagesController();
                break;
            case 'posts':
                break;
        } // end switch
        $controller->{$act}();
    } // end function

    $controllers = array("pages"=>['home', 'error'],
                         "posts"=>['index', 'show']);

    if (array_key_exists($controller, $controllers)) {
        if (in_array($action, $controllers[controller])) {
            call($controller, $action);
        }
        else {
            call('pages', 'error');
        }
    }
    else {
        call('pages', 'home');    
    }
?>
