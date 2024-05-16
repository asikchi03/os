echo "Enter a number"
read number

is_prime=true

if [ $number -lt 2 ]; then 
    is_prime=false
else 
    for ((i=2; i<=number/2; i++)); do
        if [ $((number % i)) -eq 0 ]; then 
            is_prime=false
            break
        fi 
    done
fi 

if [ "$is_prime" == true ]; then
    echo "$number is prime"
else 
    echo "$number is not prime"
fi
