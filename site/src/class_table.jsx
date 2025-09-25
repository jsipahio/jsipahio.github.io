import classes from "./data/classes.json";

export function ClassesTable() {

    function termsString(terms) {
        let str = terms[0];
        for (let i = 1; i < terms.length; ++i) {
            str += ", " + terms[i];
        }
    }

    return (
        <table>
            {classes.map(institution => {
                <th colSpan={2}>{institution["institution"]}</th>
                {institution.classes.map(classData => {
                    <tr>
                    <td>{ classData["name"] }</td>
                    <td>{ termsString(classData["terms"]) }</td>
                    </tr>
                })}
            })}
        </table>
    );
}