

class Environnement:

	def __init__(self, lar, lon, forme):
		self.capteurs = []
		self.effecteurs = []
		self.caracteristique = dict()
		self.caracteristique["longueur"] = lon
		self.caracteristique["largeur"] = lar
		self.caracteristique["forme"] = forme
		self.pos_poussiere = []
		
		
	def run(self):
		return 0

	def mesure_performance(self):
		return 0




if __name__ == __main__:
	env = Environnement(10, 10, "carre")
	env.mesure_performance()
