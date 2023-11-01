from django.db import models


class Departement(models.Model):
    numero = models.IntegerField()
    prix_m2 = models.IntegerField()

    def __str__(self):
        return f"Departement numero : {self.numero}"


class Machine(models.Model):
    nom = models.CharField(max_length=100)
    prix = models.IntegerField()

    def __str__(self):
        return f"Nom de la machine est : {self.nom}"


class Ingredient(models.Model):
    nom = models.CharField(max_length=100)

    def __str__(self):
        return f"{self.nom}"


class Prix(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    prix = models.IntegerField()

    def __str__(self):
        return f"Le cout de {self.ingredient.nom} dans le {self.departement.numero} est {self.prix} euros/kg"


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(Ingredient, on_delete=models.PROTECT)
    quantite = models.IntegerField()

    def __str__(self):
        return f"{self.quantite} kg de {self.ingredient.nom}"


class Action(models.Model):
    machine = models.ForeignKey(Machine, on_delete=models.PROTECT)
    commande = models.CharField(max_length=100)
    duree = models.IntegerField()
    ingredients = models.ManyToManyField(QuantiteIngredient)
    action = action = models.ForeignKey(
        "self", on_delete=models.PROTECT, blank=True, null=True, related_name="+"
    )

    def __str__(self):
        return f"Action : {self.commande}"


class Recette(models.Model):
    nom = models.CharField(max_length=100)
    action = models.ForeignKey(Action, on_delete=models.PROTECT)

    def __str__(self):
        return f"Nom de la recette est : {self.nom}"


class Usine(models.Model):
    departement = models.ForeignKey(Departement, on_delete=models.PROTECT)
    taille = models.IntegerField()
    machines = models.ManyToManyField(Machine)
    recettes = models.ManyToManyField(Recette)
    stocks = models.ManyToManyField(QuantiteIngredient)

    def __str__(self):
        return f"Usine ({self.departement.numero}) de {self.taille} m2"
