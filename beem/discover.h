/*
    
    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.
stantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef DISCOVER_H_INCLUDED
#define DISCOVER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define BE_PROTO_DISCOVER 6

/*  NB: Version 0 used 16 + 0/1.  That version lacked backtraces, and so
    is wire-incompatible with this version. */

#define BE_DISCOVERER (BE_PROTO_DISCOVER * 16 + 2)
#define BE_RESPONDENT (BE_PROTO_DISCOVER * 16 + 3)

#define BE_DISCOVERER_DEADLINE 1

#ifdef __cplusplus
}
#endif

#endif

