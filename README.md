# ASD1_Labo2
Site avec le test -> https://ocuisenaire.github.io/ASD1-Labs/puzzle/

Clarisse:
- écrit la fonction rotation pour qu'elle soit récursive
- écrire une fonction testant si une pièce peut être placée à un endroit (en fonction des pièces autour)

A
+------------------------+
|                  0                |
|                                    |
|                                    |
| 1                              3 |             { DAME_HAUT, GATEAU_DROIT, ARROSOIR_GAUCHE, FILLE_HAUT }
|                                    |
|                                    |
|                  2                |
+------------------------+

B
+------------------------+
|                  3                |
|                                    |
|                                    |
| 0                              2 |             { FILLE_HAUT, DAME_HAUT, GATEAU_DROIT, ARROSOIR_GAUCHE }
|                                    |
|                                    |
|                  1                |
+------------------------+

C
+------------------------+
|                  2                |
|                                    |
|                                    |
| 3                              1 |             { ARROSOIR_GAUCHE, FILLE_HAUT, DAME_HAUT, GATEAU_DROIT }
|                                    |
|                                    |
|                  0                |
+------------------------+

D
+------------------------+
|                  1                |
|                                    |
|                                    |
| 2                              0 |              { GATEAU_DROIT, ARROSOIR_GAUCHE, FILLE_HAUT, DAME_HAUT }
|                                    |
|                                    |
|                  3                |
+------------------------+


Il devrait y avoir 2 solutions différentes avec chacune 4 rotations donc solutions devrait être une liste de 8 plan de 9 pieces.
