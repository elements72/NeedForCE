if dpkg -s tilix &> /dev/null
then
    tilix --geometry=72x34 --command=./NeedForCerignola --title=NeedForCerignola
else
    echo "Installa il terminale tilix"

fi