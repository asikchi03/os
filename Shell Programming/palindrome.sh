echo "Enter a string"
read string

reverse_string=$(echo "$string" | rev)

if [ "$string" == "$reverse_string" ]; then
    echo "$string is a Palindrome"
else 
    echo "$string is not a palindrome."
fi
