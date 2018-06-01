<?php 

	class PagesController {

		public function  __construct(){}

		public function home(){
			echo "test";
			$name = "toto";
			require_once('views/pages/home.php');
		}

		public function error(){
			require_once('views/pages/error.php');
		}

	}

?>
